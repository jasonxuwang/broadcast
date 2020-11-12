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
void TCPServer::init(int32_t port){
    m_TCPSocket.as_server(port);
    m_epoll_fd  = m_epoll.epoll_init(TIMEOUT,MAXEVENT);
    m_epoll.epoll_add(m_TCPSocket.get_socket_fd());
    m_Serializer.reset();
    m_Logger.setfile("/Server/server.log");
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
                m_Logger.log( "New client connected !" , INFO);

				// record a client to user map
				User new_user;
				new_user.id = conn_sock;
                memset( new_user.m_sendbuf, '\0', BUFFSIZE );
                memset( new_user.m_recvbuf, '\0', BUFFSIZE );
                m_user_map[conn_sock] = new_user;

				// set non blocking 
				int flags = fcntl(conn_sock, F_GETFL, 0);
				if (fcntl(conn_sock, F_SETFL, flags | O_NONBLOCK) < 0){
                    m_Logger.log(  "set non blocking failed \n" , INFO);
				}

                // make epoll listening to conn_sock
				if (m_epoll.epoll_add(conn_sock) < 0){
                    m_Logger.log(  "set non blocking failed \n" , INFO);
                    continue;
                }
                
        
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
                        //std::cout << "[server]  Message From " << m_Serializer.m_Message.from() <<  ": "<< m_Serializer.m_Message.data() <<"\n";
                        //处理业务逻辑，更新玩家信息

                        int32_t changed = playerMgr.applyOp(m_Serializer.m_Message);
                        
                        //创建新更新消息
                        iMessage.set_id(playerMgr.m_players[changed].id);
                        iMessage.set_role(playerMgr.m_players[changed].role);
                        iMessage.set_status(playerMgr.m_players[changed].status);
                        iMessage.set_posx(playerMgr.m_players[changed].posx);
                        iMessage.set_posy(playerMgr.m_players[changed].posy);
                        iMessage.set_posz(playerMgr.m_players[changed].posz);
                        iMessage.set_facex(playerMgr.m_players[changed].facex);
                        iMessage.set_facey(playerMgr.m_players[changed].facey);
                        iMessage.set_facez(playerMgr.m_players[changed].facez);


                        //广播
                        memset(m_sendbuf, '\0', BUFFSIZE);
                        int32_t iMessageLength = m_Serializer.serialize(iMessage, m_sendbuf);
                        iter = m_user_map.begin();
    				    while(iter != m_user_map.end()) {
                            send(iter->first, m_sendbuf, iMessageLength + sizeof(int32_t) ,0); 
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