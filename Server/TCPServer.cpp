#include "TCPServer.h"

// //
#define PORT 10009
#define TIMEOUT 1000
#define MAXEVENT 100
#define BUFFSIZE 1024

// An implementation of TCP server
TCPServer::TCPServer(){

}

TCPServer::~TCPServer(){
    
}


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
    m_Serializer.reset();
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
                memset( new_user.m_sendbuf, '\0', BUFFSIZE );
                memset( new_user.m_recvbuf, '\0', BUFFSIZE );
                m_user_map[conn_sock] = new_user;

				// set non blocking 
				int flags = fcntl(conn_sock, F_GETFL, 0);
				if (fcntl(conn_sock, F_SETFL, flags | O_NONBLOCK) < 0){
					std::cout << "set non blocking failed \n";
				}
				m_epoll.epoll_add(conn_sock);
                
                // tell client he/she is connected
                iMessage.set_to(conn_sock);
                iMessage.set_from(-1);
                iMessage.set_data("You are connected!" + std::to_string(conn_sock));
                int iMessageLength = m_Serializer.serialize(iMessage, m_user_map[conn_sock].m_sendbuf);
                send(conn_sock,  m_user_map[conn_sock].m_sendbuf, (iMessageLength + sizeof(int32_t)), 0);
        
		// if this is an incoming message from existing connection
		}else{
        		memset( m_user_map[m_epoll_event->data.fd].m_recvbuf, '\0', BUFFSIZE );
				if ( recv(m_epoll_event->data.fd, m_user_map[m_epoll_event->data.fd].m_recvbuf,BUFFSIZE,0) != 0) {

                    std::cout << "handling client" << "\n";
                    std::map<int32_t, User>::iterator iter;
                    int32_t iMessageLength;
                    Message iMessage;

                        // print all for buffer
                        // int i ;
                        // for (i=0;i<BUFFSIZE;i++){
                        //     std::cout << m_user_map[m_epoll_event->data.fd].m_recvbuf[i];
                        // }
                        // std::cout << std::endl;

                    m_Serializer.read(m_user_map[m_epoll_event->data.fd].m_recvbuf, BUFFSIZE);
                    while(m_Serializer.deserialize() > 0){
                        
                        std::cout << "[client]  From " << m_Serializer.m_Message.from() <<  ": "<< m_Serializer.m_Message.data() <<"\n";
                        iter = m_user_map.begin();


                        // logic broad cast to all clients
    				    while(iter != m_user_map.end()) {
                            iMessage.set_to(iter->first);
                            iMessage.set_from(m_Serializer.m_Message.from());
                            iMessage.set_data(m_Serializer.m_Message.data());

                            memset( iter->second.m_sendbuf, '\0', BUFFSIZE );
                            iMessageLength = m_Serializer.serialize(iMessage, iter->second.m_sendbuf);
                            send(iter->first, iter->second.m_sendbuf, (iMessageLength + sizeof(int32_t)), 0);
            			    fprintf(stderr,"[server] send to: %d\n", iter->first);
        				    iter++;
    				    }
                    }
    			}else{
					// if recv returns 0, close the connection and unregister the user
                    std::cout << "[server] Client " << m_epoll_event->data.fd << " left \n";
					m_epoll.epoll_close(m_epoll_event->data.fd); //?
					m_user_map.erase(m_epoll_event->data.fd);
				}
        }
    }
}