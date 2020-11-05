#include "TCPClient.h"
#define PORT 10006
#define TIMEOUT 1000
#define MAXEVENT 100
#define BUFFSIZE 1024
#define IPSTR "127.0.0.1"



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
                
                std::cout << "now buffer is: " <<  m_recvbuf << "\n";
                // get message length from buffer
                int iMessageLength = decode_int32(m_recvbuf);
                std::cout << "now messagelen is: " <<  iMessageLength << "\n";

                // get message from buffer
                Message iMessage;
                get_message(m_recvbuf+sizeof(int32_t), iMessageLength, &iMessage );
                std::cout << "[client]  From " << iMessage.from() <<  ": "<< iMessage.data() <<"\n";

                // Message iMessage;
                // iMessage.ParseFromArray(m_recvbuf, strlen(m_recvbuf));
                // std::cout << "[client]  From " << iMessage.from() <<  ": "<< iMessage.data() <<"\n";
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

                        // get the length of message
                        int32_t iMessageLength = iMessage.ByteSizeLong();
                        std::cout << "2 message len is: " <<  iMessageLength << "\n";
                        // construct header
                        encode_int32(m_sendbuf, iMessageLength);
                        
                        // add header byte 
                        if (!iMessage.SerializeToArray(m_sendbuf+sizeof(int32_t), iMessage.ByteSizeLong()) ){
                            std::cout << "2 serailzation failed!! \n";
                        } // TODO:caution overflow

                        std::cout <<  "[client] sendbuf now is :" << m_sendbuf+sizeof(int32_t) << std::endl ;
                        send(m_TCPSocket.get_socket_fd(), m_sendbuf,iMessageLength + sizeof(int32_t) ,0);
                }

        }else{
            return;
        }

    }
}