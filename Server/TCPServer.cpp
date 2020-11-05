#include "TCPServer.h"

// //
#define PORT 10008
#define TIMEOUT 1000
#define MAXEVENT 100
#define BUFFSIZE 1024


int32_t encode_int32(char *iBuff,  int32_t iMessageLength) {
    char bytes[4];
    bytes[0] = (iMessageLength>>24) & 0xFF;
    bytes[1] = (iMessageLength>>16) & 0xFF;
    bytes[2] = (iMessageLength>>8) & 0xFF;
    bytes[3] = (iMessageLength) & 0xFF;
    memcpy(iBuff, bytes, sizeof(bytes));
    return sizeof(int32_t);
}

int32_t decode_int32(char *iBuff) {
    int num = 0;
    for (int i=0;i<4;i++){
        num<<8;
        num |= iBuff[i];
    }
    return num;
}



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
				User new_user;
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
        		memset( m_user_map[m_epoll_event->data.fd].m_recvbuf, '\0', BUFFSIZE );
				if ( recv(m_epoll_event->data.fd, m_user_map[m_epoll_event->data.fd].m_recvbuf,BUFFSIZE,0) != 0) {
                     std::cout << "handling client" << "\n";
                    int32_t iMessageLength;
                    Message iMessage;
                    std::map<int32_t, User>::iterator iter;
                    int32_t offset = 0;
                    do{
                        iMessageLength = decode_int32(m_user_map[m_epoll_event->data.fd].m_recvbuf+offset);
                        get_message(m_user_map[m_epoll_event->data.fd].m_recvbuf+ offset+sizeof(int32_t), iMessageLength, &iMessage );
                        std::cout << "[client]  From " << iMessage.from() <<  ": "<< iMessage.data() <<"\n";
                        offset +=iMessageLength;
    				    iter = m_user_map.begin();
    				    while(iter != m_user_map.end()) {
                            iMessage.set_to(iter->first);
                        // set buffer empty
                            memset( iter->second.m_sendbuf, '\0', BUFFSIZE );
                            int32_t iMessageLength = iMessage.ByteSizeLong();
                        // construct header
                            encode_int32(iter->second.m_sendbuf,iMessageLength );
                            iMessage.SerializeToArray(iter->second.m_sendbuf+sizeof(int32_t), iMessage.ByteSizeLong()); // TODO:caution overflow
						    send(iter->first, iter->second.m_sendbuf, (iMessageLength + sizeof(int32_t)), 0);
            			    fprintf(stderr,"[server] send to: %d\n\n", iter->first);
        				    iter++;
    				    }

                    }while(iMessageLength>0);

                    // get message length from buffer
                    // int iMessageLength = decode_int32(m_user_map[m_epoll_event->data.fd].m_recvbuf);
                    // std::cout << "message length from client is : " << iMessageLength << "\n";
                    // get message from buffer
                   
                    // create a Message class. from server, send to user id
                    // Message iMessage;
                    // iMessage.set_from(m_epoll_event->data.fd);
                    // // iMessage.set_to();
                    // iMessage.set_data(std::string(m_recvbuf));

                    // iterate over usermap, broadcast message.
		

    			}else{
					// if recv returns 0, close the connection and unregister the user
					m_epoll.epoll_close(m_epoll_event->data.fd); //?
					m_user_map.erase(m_epoll_event->data.fd);
				}
        }
    }
}