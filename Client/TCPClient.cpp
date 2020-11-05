#include "TCPClient.h"
#define PORT 10002
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
                std::cout << "[client] recv: " << m_recvbuf << "\n";
            }

        // if user input, read it into buffer and send to server.
        }else if(m_epoll_event->data.fd == STDIN_FILENO){
                memset(m_sendbuf, '\0', BUFFSIZE);
                fgets(m_sendbuf);
                if (strlen(m_sendbuf) > 0 ){
                    send(m_TCPSocket.get_socket_fd(), m_sendbuf, strlen(m_sendbuf),0);
                }

        }else{
            return;
        }

    }
}