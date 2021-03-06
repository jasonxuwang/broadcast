#include "TCPGate.h"

// //

// An implementation of TCP server
TCPGate::TCPGate(){
    
}

TCPGate::~TCPGate(){
    
}

/*
    Init function creates required objects for a TCP server including:
        1 a TCP socket
        2 an epoll object
    and adds one socket to epoll to monitor events：
        1 current socket file descriptor.

*/

void TCPGate::connect_servers(std::string conf_path){
    // read server info from server.conf 
    for (int i = 0; i < sizeof(serverInfos) / sizeof(ServerInfo); i++ ){
        // create socket
        TCPSocket tsock;
        tsock.as_client(serverInfos[i].ipstr,serverInfos[i].port);
        if (tsock.get_socket_fd() <0){
            std::cout << "[gate] error connecting to server "  <<   serverInfos[i].ipstr<<  " " <<  serverInfos[i].port  <<"!\n";
        }else{
            Servers serv;
            serv.server_id = i;
            serv.m_sock = tsock;
            std::cout << "[gate] connected to server "  <<   serverInfos[i].ipstr<<  " " <<  serverInfos[i].port  <<"!\n";
            // add this server to servers
            m_servers[tsock.get_socket_fd()] = serv;

            // add this socket to Epoll handler.
            m_epoll.epoll_add(tsock.get_socket_fd()); // 监听服务器的socket加入Epoll
        }
    }
}

void TCPGate::init(){
    m_ClientsHanldeSocket.as_server(GATE_PORT); // 负责监听用户新连接
    std::cout << "[gate] Client handling socket established!";
    m_epoll_fd  = m_epoll.epoll_init(TIMEOUT,MAXEVENT); // Epoll处理所有socket的事件
    m_epoll.epoll_add(m_ClientsHanldeSocket.get_socket_fd()); // 监听用户连接的socket加入Epoll

    connect_servers("./Server/servers.conf"); //尝试与所有服务器建立连接
    m_Serializer.reset();
    m_Logger.setfile("/Server/gate.log");
}

/* main loop, keep query events from epoll */
void TCPGate::run(){
    while(1){
        poll();
    }
}


int32_t TCPGate::assign_server(int32_t tClientId){

    // simple hash 

    auto end = m_servers.end(); 
    int counter = 0;
    for (auto it = m_servers.begin(); it != end; ++it) {
        
        if (counter == tClientId%m_servers.size()) return it->first;
        counter++;
    }
    return 0;
}

/* single query events from epoll */
void TCPGate::poll(){
    int numfd = m_epoll.wait();

    // for each event
    int n;
    for (n=0; n<numfd;n++){
        m_epoll_event = m_epoll.get_event_by_id(n); // get event id

        // if this is a new client
        if (m_epoll_event->data.fd == m_ClientsHanldeSocket.get_socket_fd()){
				int32_t conn_sock = m_ClientsHanldeSocket.Accept();
                m_Logger.log( "[gate] New client connected !" , INFO);


				// set non blocking 
				int flags = fcntl(conn_sock, F_GETFL, 0);
				if (fcntl(conn_sock, F_SETFL, flags | O_NONBLOCK) < 0){
                    m_Logger.log(  "set non blocking failed \n" , INFO);
				}

                // make epoll listening to conn_sock
				if (m_epoll.epoll_add(conn_sock) < 0){
                    m_Logger.log(  "set epoll listening failed \n" , INFO);
                    continue;
                }
                
                // store this client to user map
				Clients new_client;
				new_client.client_id = conn_sock;
                memset( new_client.m_sendbuf, '\0', BUFFSIZE );
                memset( new_client.m_recvbuf, '\0', BUFFSIZE );
                // assign a server for this client。 TODO:分配逻辑需要改进
                // new_client.server_fd = m_servers[conn_sock%2].m_sock.get_socket_fd();
                new_client.server_fd = assign_server(new_client.client_id);
                std::cout << "server assigned to this client is "<< new_client.server_fd  << "\n";
                m_clients[conn_sock] = new_client;


                // tell client he/she is connected and he/she's id; TODO
                Message iMessage;
                iMessage.set_to(conn_sock);
                iMessage.set_from(-1);
                iMessage.set_data("You are connected, your id is: " + std::to_string(conn_sock) + ", your server is: " + std::to_string(new_client.server_fd));
                int iMessageLength = m_Serializer.serialize(iMessage, m_clients[conn_sock].m_sendbuf);
                send(conn_sock,  m_clients[conn_sock].m_sendbuf, (iMessageLength + sizeof(int32_t)), 0);
        
		// if this is an incoming message from existing connection
		}else{

            /**
             *如果是接受已经存在的socket发送消息，分为server 和client两部分处理
             *  1.from server，是这个server加上了自己的信息，应该加上server id以后将其转发到所有client
             *  2. from client, 是这个client发送了消息，应该将其转发到它对应的server
             */
            // 判断是从哪里来

            //如果是从client来
            if (m_clients.find(m_epoll_event->data.fd) != m_clients.end()) {  
                    std::cout << "[gate] msg from client " <<m_epoll_event->data.fd << "\n";  
                // 解包
                if ( recv(m_epoll_event->data.fd, m_clients[m_epoll_event->data.fd].m_recvbuf,BUFFSIZE,0) != 0) {

                        //打印看看收到了什么. 这里正常收到

                        int32_t tMessageLength;
                        Message tMessage;

                        // initialize serailizer with buffer data
                        m_Serializer.read(m_clients[m_epoll_event->data.fd].m_recvbuf, BUFFSIZE);

                        // deal with 粘包
                        // if the serializer can decode message object from the buffer
                        while(m_Serializer.deserialize() > 0){
                            // get the fd of target server
                            int32_t tTargetServerFd = m_clients[m_epoll_event->data.fd].server_fd;
                            std::cout << "[gate]  From client:" <<m_Serializer.m_Message.from() <<" To server:"<<tTargetServerFd <<  " Message: "<< m_Serializer.m_Message.data() <<"\n";

                            // 如果decode到一个message，发给server
                            // 该client对应的server fd是m_clients[m_epoll_event->data.fd].server_fd
                            // construct a new message, 原封不动发给server
                            tMessage.set_to(m_Serializer.m_Message.to());
                            tMessage.set_from(m_Serializer.m_Message.from());
                            tMessage.set_data(m_Serializer.m_Message.data());

                           
                            memset(m_servers[tTargetServerFd].m_sendbuf, '\0', BUFFSIZE); // 清空对应的发送缓存
                            // set the server's send buffer
                            tMessageLength = m_Serializer.serialize(tMessage, m_servers[tTargetServerFd].m_sendbuf);
                            // send to server the client's message
                            send(tTargetServerFd, m_servers[tTargetServerFd].m_sendbuf, (tMessageLength + sizeof(int32_t)), 0);

                        }

                // if recv returns 0, close the connection and unregister the user
    			}else{
                    std::cout << "[server] Client " << m_epoll_event->data.fd << " has left\n";
                    if (m_epoll.epoll_close(m_epoll_event->data.fd) < 0){
                        std::cout << "not closed properly! \n";
                    }
					m_epoll.epoll_close(m_epoll_event->data.fd); //?
					m_clients.erase(m_epoll_event->data.fd);
				}

            // 如果是从server来
            }else if(m_servers.find(m_epoll_event->data.fd) != m_servers.end()){ 
                    // std::cout << "[gate] msg from server " <<m_epoll_event->data.fd << "\n";  
                    //TODO: 群发给所有client
                    //清空该server fd的缓冲区以便接受数据
                    memset(m_servers[m_epoll_event->data.fd].m_recvbuf, '\0', BUFFSIZE); // clear receive buffer
                    if (recv(m_epoll_event->data.fd, m_servers[m_epoll_event->data.fd].m_recvbuf, BUFFSIZE,0) != 0){
                       
                        m_Serializer.read(m_servers[m_epoll_event->data.fd].m_recvbuf, BUFFSIZE);
                        int32_t tMessageLength;
                        Message tMessage;
                        std::map<int32_t, Clients>::iterator iter;
                        while(m_Serializer.deserialize() > 0){
                            std::cout << "[gate]  broadcasting to all... " << m_Serializer.m_Message.from() <<  ": "<< m_Serializer.m_Message.data() <<"\n";
                            //TODO: 群发给所有client
                            iter = m_clients.begin();
    				        while(iter != m_clients.end()) {
                                /// 构造message
                                tMessage.set_to(iter->first);
                                tMessage.set_from(m_Serializer.m_Message.from());
                                tMessage.set_data(std::string("[gate: via server ") + std::to_string(m_epoll_event->data.fd) + "]"+ m_Serializer.m_Message.data());

                                
                                std::cout << iter->first  << "\n";
                                // // 清空client socket fd的缓冲区
                                memset(iter->second.m_sendbuf, '\0', BUFFSIZE);

                                //  // convert the message object to char array // send to client
                                tMessageLength = m_Serializer.serialize(tMessage, iter->second.m_sendbuf);
                                send(iter->first, iter->second.m_sendbuf, (tMessageLength + sizeof(int32_t)), 0);
            			        fprintf(stderr,"[gates] Sent to: %d\n", iter->first);
        				        iter++;
                            }
                        }
                    }else{
                        std::cout << "[gate] server " << m_epoll_event->data.fd << " has disconnected\n";
                        if (m_epoll.epoll_close(m_epoll_event->data.fd) < 0){
                            std::cout << "not closed properly! \n";
                        }
                        m_epoll.epoll_close(m_epoll_event->data.fd); //?
                        m_servers.erase(m_epoll_event->data.fd);
                    }


                    m_Serializer.reset();


            }else{ //不是client也不是server
                std::cout << "event come from " <<m_epoll_event->data.fd << "does not from clientor server\n";  
            }



               
        }
    }
}