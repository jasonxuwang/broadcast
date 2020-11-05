#include "TCPServer.h"

// //
#define PORT 10003
#define TIMEOUT 1000
#define MAXEVENT 100
#define BUFFSIZE 1024


// An implementation of TCP server
TCPServer::TCPServer(){

}

TCPServer::~TCPServer(){
    
}

/*
    Init function creates required objects for a TCP server including:
        1 a TCP socket
        2 an epoll object
    and adds one socket to epoll to monitor events：
        1 current socket file descriptor.

*/
void TCPServer::init(){
    m_TCPSocket.as_server(PORT);
    m_epoll_fd  = m_epoll.epoll_init(TIMEOUT,MAXEVENT);
    m_epoll.epoll_add(m_TCPSocket.get_socket_fd());
}

/* main loop, keep query events from epoll */
void TCPServer::run(){
    while(1){
        poll();
    }
}




/* single query events from epoll */
void TCPServer::poll(){
    int numfd = m_epoll.wait();
    int n;

    // for each event
    for (n=0; n<numfd;n++){
        m_epoll_event = m_epoll.get_event_by_id(n); // get event id

        // if this is a new client
        if (m_epoll_event->data.fd == m_TCPSocket.get_socket_fd()){
				int32_t conn_sock = m_TCPSocket.accept_conn();
				std::cout << "new client connected ! \n";

				// store client fd to user map
				User new_user = {0};
				new_user.id = conn_sock;
				m_user_map[conn_sock] = new_user;
				
				// set non blocking 
				int flags = fcntl(conn_sock, F_GETFL, 0);
				if (fcntl(conn_sock, F_SETFL, flags | O_NONBLOCK) < 0){
					std::cout << "set non blocking failed \n";
				}
				m_epoll.epoll_add(conn_sock);
        
		// if this is an incoming message from esiting connection
		}else{
        		memset( m_recvbuf, '\0', BUFFSIZE );
				if ( recv(m_epoll_event->data.fd, m_recvbuf,BUFFSIZE,0) != 0) {
            		//fprintf(stderr,"[server] recv msg: %s\n", m_recvbuf);
                    // process: read sizeof(int32_t) bytes first, if m_recvbuf < this value, error;
                    // process: convert that much bytes to a messagehead class, get the length of consecutive message
                    // process: read m_length bytes then. if OK, continue to read untill there are no bytes in buffer
                    // process: if not enough bytes.
                    // process:     1. if not reach the end of buffer, error
                    // proecss:     2. if reached the end of buffer, holdon and wait for next incoming message. 

                    // get message length from buffer
                    int iMessageHeaderLength =  sizeof(int32_t);
                    int iMessageLength = get_message_len(m_recvbuf,iMessageHeaderLength);
                    if (iMessageLength < 0){
                        continue;
                    }

                    // get message from buffer
                    Message iMessage;
                    get_message(m_recvbuf+iMessageHeaderLength, iMessageLength, *iMessage );
                    std::cout << "[client]  From " << iMessage.from() <<  ": "<< iMessage.data() <<"\n";

                    // create a Message class. from server, send to user id
                    // Message iMessage;
                    // iMessage.set_from(m_epoll_event->data.fd);
                    // // iMessage.set_to();
                    // iMessage.set_data(std::string(m_recvbuf));

                    // iterate over usermap, broadcast message.
					std::map<int32_t, User>::iterator iter;
    				iter = m_user_map.begin();
    				while(iter != m_user_map.end()) {
                        iMessage.set_to(iter->first);

                        // set buffer empty
                        memset( m_sendbuf, '\0', BUFFSIZE );

                        int32_t iMessageLength = iMessage.ByteSizeLong();
                        // construct header
                        MessageHead iMessageHead;
                        iMessageHead.m_Length = iMessageLength;

                        // add header byte 
                        if (strlen(m_sendbuf) < 0){
                            continue;
                        }
                        int32_t iMessageHeadLength = iMessageHead.toBytes(m_sendbuf);
                        iMessage.SerializeToArray(m_sendbuf+iMessageHeadLength, iMessage.ByteSizeLong()); // TODO:caution overflow


                        // iMessage.SerializeToArray(m_recvbuf, iMessage.ByteSizeLong()); // TODO:caution overflow
						send(iter->first, m_sendbuf, strlen(m_sendbuf), 0);

            			fprintf(stderr,"[server] send to: %d\n\n", iter->first);
        				iter++;
    				}

    			}else{
					// if recv returns 0, close the connection and unregister the user
					m_epoll.epoll_close(m_epoll_event->data.fd); //?
					m_user_map.erase(m_epoll_event->data.fd);
				}
        }
    }
}