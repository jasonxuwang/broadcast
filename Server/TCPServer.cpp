#include <stdint.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>
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
#include <string>
#include <sys/epoll.h>
#include <map>
#include <iostream>
#include "../Commons/Epoll.h"
#include "../Commons/TCPSocket.h"
#include "TCPServer.h"
// //
#define PORT 10002
#define TIMEOUT 1000
#define MAXEVENT 100




TCPServer::TCPServer(){

}

TCPServer::~TCPServer(){
    
}

void TCPServer::init(){
    m_TCPSocket.as_server(PORT);
    m_epoll_fd  = m_epoll.epoll_init(TIMEOUT,MAXEVENT);
    m_epoll.epoll_add(m_TCPSocket.get_socket_fd());
}

void TCPServer::run(){
    while(1){
        poll();
    }
}

void TCPServer::poll(){
    int numfd = m_epoll.wait();
    int n;
	// struct epoll_event * iEpollEvent; 
    // refresh iEpollEvent
    for (n=0; n<numfd;n++){
        m_epoll_event = m_epoll.get_event_by_id(n);
        if (m_epoll_event->data.fd == m_TCPSocket.get_socket_fd()){
				int32_t conn_sock = m_TCPSocket.accept_conn();
				std::cout << "new client connected ! \n";
				// add client to user map
				User new_user = {0};
				new_user.id = conn_sock;
				m_user_map[conn_sock] = new_user;
				
				// set non blocking 
				int flags = fcntl(conn_sock, F_GETFL, 0);
				if (fcntl(conn_sock, F_SETFL, flags | O_NONBLOCK) < 0){
					std::cout << "set non blocking failed \n";
				}
				m_epoll.epoll_add(conn_sock);
        
			// if incoming message	
		}else{
           
        		memset( m_recvbuf, '\0', BUFFSIZ );

				if ( recv(m_epoll_event->data.fd, m_recvbuf,BUFSIZ,0) != 0) {
					if (!strcmp(m_recvbuf, "exit")) break;
            		fprintf(stderr,"[server] recv msg: %s\n", m_recvbuf);

					std::map<int32_t, User>::iterator iter;
    				iter = m_user_map.begin();

    				while(iter != m_user_map.end()) {
						send(iter->first, m_recvbuf, strlen(m_recvbuf), 0);
            			fprintf(stderr,"[server] send to: %d\n\n", iter->first);
        				iter++;
    				}
            		
    			}else{
					// if recv returns 0, close the connection and unregister the user
					m_epoll.epoll_close(m_epoll_event->data.fd); //?
					m_user_map.erase(m_epoll_event->data.fd);
				}
        }
    }
}