#include "TCPServer.h"

// //

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
    m_Serializer.reset();
    m_Logger = m_Logger(std::string(LOG_FOLDER)+LOG_SERVER_FILE);
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

    // for each event
    int n;
    for (n=0; n<numfd;n++){
        m_epoll_event = m_epoll.get_event_by_id(n); // get event id

        // if this is a new client
        if (m_epoll_event->data.fd == m_TCPSocket.get_socket_fd()){
				int32_t conn_sock = m_TCPSocket.Accept();
				std::cout << "new client connected ! \n";

				// record a client to user map
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

                // make epoll listening to conn_sock
				if (m_epoll.epoll_add(conn_sock) < 0){
                    std::cout << "epoll add error for socket " << conn_sock << std::endl;
                    continue;
                }
                
                // tell client he/she is connected and he/she's id;
                Message iMessage;
                iMessage.set_to(conn_sock);
                iMessage.set_from(-1);
                iMessage.set_data("You are connected, your id is: " + std::to_string(conn_sock));
                int iMessageLength = m_Serializer.serialize(iMessage, m_user_map[conn_sock].m_sendbuf);
                send(conn_sock,  m_user_map[conn_sock].m_sendbuf, (iMessageLength + sizeof(int32_t)), 0);
        
		// if this is an incoming message from existing connection
		}else{
                // clear client buffer
        		memset( m_user_map[m_epoll_event->data.fd].m_recvbuf, '\0', BUFFSIZE );

                // if read someting from kernel.
				if ( recv(m_epoll_event->data.fd, m_user_map[m_epoll_event->data.fd].m_recvbuf,BUFFSIZE,0) != 0) {

                    std::map<int32_t, User>::iterator iter;
                    int32_t iMessageLength;
                    Message iMessage;

                    // initialize serailizer with buffer data
                    m_Serializer.read(m_user_map[m_epoll_event->data.fd].m_recvbuf, BUFFSIZE);

                    // deal with 粘包
                    // if the serializer can decode message object from the buffer
                    while(m_Serializer.deserialize() > 0){
                        std::cout << "[server]  Message From " << m_Serializer.m_Message.from() <<  ": "<< m_Serializer.m_Message.data() <<"\n";

                        // logic: broad cast to all clients
                        iter = m_user_map.begin();
    				    while(iter != m_user_map.end()) {

                            // construct message
                            iMessage.set_to(iter->first);
                            iMessage.set_from(m_Serializer.m_Message.from());
                            iMessage.set_data(m_Serializer.m_Message.data());

                            memset( iter->second.m_sendbuf, '\0', BUFFSIZE ); // clear send buffer

                            // convert the message object to char array in format size (4 bytes) | char array of message body (generated by protobuf)
                            iMessageLength = m_Serializer.serialize(iMessage, iter->second.m_sendbuf);

                            // send to client
                            send(iter->first, iter->second.m_sendbuf, (iMessageLength + sizeof(int32_t)), 0);
            			    fprintf(stderr,"[server] Sent to: %d\n", iter->first);
        				    iter++;
    				    }
                    }

                // if recv returns 0, close the connection and unregister the user
    			}else{
                    std::cout << "[server] Client " << m_epoll_event->data.fd << " has left\n";
                    if (m_epoll.epoll_close(m_epoll_event->data.fd) < 0){
                        std::cout << "not closed properly! \n";
                    }
					m_epoll.epoll_close(m_epoll_event->data.fd); //?
					m_user_map.erase(m_epoll_event->data.fd);
				}
        }
    }
}