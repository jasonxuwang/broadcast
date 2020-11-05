
#include <sys/epoll.h>
#include <stdint.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <stdlib.h>

#include <signal.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <net/if.h>
#include <dirent.h>
#include <dlfcn.h>
#include <sys/select.h>
#include <assert.h>
#include <iostream>
#include <string>
#include "Epoll.h"
#include "TCPSocket.h"
// #include "message.pb.h"
#define TIMEOUT 1000
#define MAXEVENT 100

#define PORT  10002

int main (){
    char ipstr[] = "127.0.0.1";  
    TCPSocket m_TCPSocket;
    m_TCPSocket.as_client(ipstr,PORT);	

    // create epoll handle
    int conn_sock;
    Epoll m_epoll;
	int32_t epoll_fd  = m_epoll.epoll_init(TIMEOUT,MAXEVENT);
    std::cout << "[client] epoll created !\n";
	m_epoll.epoll_add(m_TCPSocket.get_socket_fd());
    std::cout << "[client] listening socket added to epoll! \n";
    m_epoll.epoll_add(STDIN_FILENO);
    std::cout << "[client] stdin socket added to epoll! \n";
	

    char sendbuf[BUFSIZE];
    char recvbuf[BUFSIZE];
    while(1) {
        int numfd = m_epoll.wait();
        // if (numfd > 0){
		// 	std::cout << "[client] num of events:" << numfd << std::endl ;
		// }
        int n;
        struct epoll_event * iEpollEvent; 
        for (n=0; n<numfd;n++){
            // if data incoming from remote
            iEpollEvent = m_epoll.get_event_by_id(n);
            if (iEpollEvent->data.fd == m_TCPSocket.get_socket_fd()){
                memset( recvbuf, '\0', BUFSIZE );
                if ( recv(iEpollEvent->data.fd, recvbuf,BUFSIZE,0) != 0) {
                     std::cout << "[client] recv back: "  <<  recvbuf << "\n";
                }
               
               

            // if input, ask usr input
            }else if (iEpollEvent->data.fd == STDIN_FILENO){
                memset( sendbuf, '\0', BUFSIZE );
                gets(sendbuf);
                if (strlen(sendbuf) > 0)
                    send(m_TCPSocket.get_socket_fd(),sendbuf,strlen(sendbuf),0);
            }else{
                return -1;
            }

        }
    }
    return 0;
}
