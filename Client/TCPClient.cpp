#include "TCPClient.h"

// An implementation of TCP client
TCPClient::TCPClient(){

}

TCPClient::~TCPClient(){
    
}

/*
    Init function creates required objects for a TCP client including:
        1 a TCP socket
        2 an epoll object
    and adds two sockets to epoll to monitor events：
        1 socket file descriptor of connection with server.
        2 stdin (user input).
*/
void TCPClient::init(char* ipstr,int32_t port){
    m_TCPSocket.as_client(ipstr,port);
    m_epoll_fd  = m_epoll.epoll_init(TIMEOUT,MAXEVENT);
    m_epoll.epoll_add(m_TCPSocket.get_socket_fd());
    m_epoll.epoll_add(STDIN_FILENO);
    m_Serializer.reset();
}


/*
    main loop, keep seeing whether there is any event.
*/
void TCPClient::run(){
    while (1){
        poll();
    }
}

/*
    poll function performs one query, see if any incoming events are captureed. 
*/
void TCPClient::poll(){
    int numfd = m_epoll.wait();
    int n;

    // process each event
    for (n=0; n<numfd;n++){
        m_epoll_event = m_epoll.get_event_by_id(n); // get event id

        // if there is a message from server, update my id.
        if (m_epoll_event->data.fd == m_TCPSocket.get_socket_fd()){

            memset(m_recvbuf, '\0', BUFFSIZE); // clear receive buffer

            // server tell me my id, update.
            if (recv(m_epoll_event->data.fd, m_recvbuf, BUFFSIZE,0) != 0){
                m_Serializer.read(m_recvbuf, BUFFSIZE);
                while(m_Serializer.deserialize() > 0){
                    m_id = m_Serializer.m_Message.to();
                    std::cout << "[client]  From " << m_Serializer.m_Message.from() <<  ": "<< m_Serializer.m_Message.data() <<"\n";
                }
                m_Serializer.reset();
            }

        // if user input, read it into buffer and send to server.
        }else if(m_epoll_event->data.fd == STDIN_FILENO){
                memset(m_recvbuf, '\0', BUFFSIZE);
                gets(m_recvbuf); // TODO: switch to a safer approach

                // if user input some data
                if (strlen(m_recvbuf) > 0 ){
                        // construct message  
                        Message iMessage;
                        iMessage.set_data(std::string(m_recvbuf));
                        iMessage.set_to(0);
                        iMessage.set_from(m_id);

                        // serialize to m_sendbuf
                        memset(m_sendbuf, '\0', BUFFSIZE);
                        int32_t iMessageLength = m_Serializer.serialize(iMessage, m_sendbuf);
                        //int32_t iMessageLength2 = m_Serializer.serialize(iMessage, m_sendbuf+iMessageLength+sizeof(int32_t)); // 粘包测试

                        // send to server
                        send(m_TCPSocket.get_socket_fd(), m_sendbuf, iMessageLength + sizeof(int32_t) ,0); 
                        //send(m_TCPSocket.get_socket_fd(), m_sendbuf, iMessageLength + iMessageLength2 + sizeof(int32_t)+ sizeof(int32_t) ,0);// 粘包测试
        

                }

        }else{
            return;
        }

    }
}