

#include "TCPClient.h"
#define PORT 10002
#define TIMEOUT 1000
#define MAXEVENT 100
#define BUFFSIZE 1024
#define IPSTR "127.0.0.1"

TCPClient::TCPClient(){

}

TCPClient::~TCPClient(){
    
}

void TCPClient::init(){
    m_TCPSocket.as_client(IPSTR,PORT);
    m_epoll_fd  = m_epoll.epoll_init(TIMEOUT,MAXEVENT);
    m_epoll.epoll_add(m_TCPSocket.get_socket_fd());
    m_epoll.epoll_add(STDIN_FILENO);

}

void TCPClient::run(){
    while (1){
        poll();
    }
}

void TCPClient::poll(){
    int numfd = m_epoll.wait();
    int n;
    for (n=0; n<numfd;n++){
        m_epoll_event = m_epoll.get_event_by_id(n);
        if (m_epoll_event->data.fd == m_TCPSocket.get_socket_fd()){
            memset(m_recvbuf, '\0', BUFFSIZE);
            if (recv(m_epoll_event->data.fd, m_recvbuf, BUFFSIZE,0) != 0){
                std::cout << "[client] recv: " << m_recvbuf << "\n";
            }
        }else if(m_epoll_event->data.fd == STDIN_FILENO){
                memset(m_sendbuf, '\0', BUFFSIZE);
                gets(m_sendbuf);
                if (strlen(m_sendbuf) > 0 ){
                    send(m_TCPSocket.get_socket_fd(), m_sendbuf, strlen(m_sendbuf),0);
                }

        }else{
            return -1;
        }

    }
}