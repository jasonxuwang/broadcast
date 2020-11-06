#include "TCPClient.h"
#define PORT 10009
#define TIMEOUT 1000
#define MAXEVENT 100
#define BUFFSIZE 1024
#define IPSTR "127.0.0.1"




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
void TCPClient::init(){
    m_TCPSocket.as_client(IPSTR,PORT);
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
        
        // if there is a message from server, simply print it out.
        if (m_epoll_event->data.fd == m_TCPSocket.get_socket_fd()){
            memset(m_recvbuf, '\0', BUFFSIZE);
            if (recv(m_epoll_event->data.fd, m_recvbuf, BUFFSIZE,0) != 0){
                // 如果读取到信息
                // std::cout << "recv buffer is now : " << m_recvbuf << "\n";
                m_Serializer.read(m_recvbuf, BUFFSIZE);
                while(m_Serializer.deserialize() > 0){
                    std::cout << "[client]  From " << m_Serializer.m_Message.from() <<  ": "<< m_Serializer.m_Message.data() <<"\n";
                }
            }

        // if user input, read it into buffer and send to server.
        }else if(m_epoll_event->data.fd == STDIN_FILENO){
                memset(m_recvbuf, '\0', BUFFSIZE);
                gets(m_recvbuf);

                if (strlen(m_recvbuf) > 0 ){
                        // tes
                        std::cout << "2 now recvbuf is: " <<  m_recvbuf << "\n";
                        Message iMessage;
                        iMessage.set_data(std::string(m_recvbuf));
                        iMessage.set_to(-1);
                        iMessage.set_from(2);


                        int32_t iMessageLength = m_Serializer.serialize(iMessage, m_sendbuf);
                        std::cout <<  "[client] sendbuf now is :" << m_sendbuf+sizeof(int32_t)<< std::endl;

                        iMessageLength = m_Serializer.serialize(iMessage, m_sendbuf+iMessageLength+sizeof(int32_t));


                        send(m_TCPSocket.get_socket_fd(), m_sendbuf, 2*(iMessageLength + sizeof(int32_t)) ,0);

                }

        }else{
            return;
        }

    }
}