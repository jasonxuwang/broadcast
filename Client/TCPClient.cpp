#include "TCPClient.h"
#define PORT 10005
#define TIMEOUT 1000
#define MAXEVENT 100
#define BUFFSIZE 1024
#define IPSTR "127.0.0.1"



int32_t encode_int32(char **pOut,  uint32_t Src) {
    if (NULL == pOut || NULL == *pOut) {
        return 0;
    }

    *(uint32_t*)(*pOut) = htonl(Src);
    *pOut += sizeof(uint32_t);
    return int32_t(sizeof(uint32_t));
}

int32_t decode_int32(char **pIn,  uint32_t *pOut) {
    if (NULL == pIn || NULL == *pIn || NULL == pOut) {
        return 0;
    }
    *pOut = (uint32_t) ntohl((uint32_t)*(uint32_t*)(*pIn));
    *pIn += sizeof(uint32_t);
    return int32_t(sizeof(uint32_t));
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
                int iMessageLength = get_message_len(m_recvbuf,sizeof(int32_t));
                if (iMessageLength < 0){
                    continue;
                }
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
                        char bytes[4];
                        bytes[0] = (n>>24) & 0xFF;
                        bytes[1] = (n>>16) & 0xFF;
                        bytes[2] = (n>>8) & 0xFF;
                        bytes[3] = (n) & 0xFF;
                        memcpy(m_sendbuf, bytes, sizeof(bytes));
                        printf("first bytes of buffer now is set to %s \n", m_sendbuf);


                        // add header byte 
                        if (!iMessage.SerializeToArray(m_sendbuf+sizeof(int32_t), iMessage.ByteSizeLong()) ){
                            std::cout << "2 serailzation failed!! \n";
                        } // TODO:caution overflow

                        std::cout <<  "2 sendbuf len = :" << strlen(m_sendbuf) <<  "[client] sendbuf now is :" << m_sendbuf << std::endl ;
                        send(m_TCPSocket.get_socket_fd(), m_sendbuf, strlen(m_sendbuf),0);
                }

        }else{
            return;
        }

    }
}