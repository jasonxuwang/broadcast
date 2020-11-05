
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
// #include "message.pb.h"
#include "Epoll.h"
#include "TCPSocket.h"

#define PORT 10002
#define TIMEOUT 1000
#define MAXEVENT 100

struct User{
	int32_t id;
};


void read_from(int32_t fd){
	// process the connection
	// 1. read all bytes from the buffer 
	ssize_t n;
    	char buf[1024];
    	while((n=read(fd,buf,1024)) > 0)
        write(fd,buf,n);
}



int main(){

// test protobuf
// create an epoll object;


// create a user map
std::map<int32_t, User> user_map;
// create a socket
	TCPSocket m_TCPSocket;
	m_TCPSocket.as_server(PORT);
	
	// create epoll 
	int conn_sock;
	Epoll m_epoll;
	int32_t epoll_fd  = m_epoll.epoll_init(TIMEOUT,MAXEVENT);
	m_epoll.epoll_add(m_TCPSocket.get_socket_fd());

	while (1){
		// get events from epoll
		int numfd = m_epoll.wait();
		
		int n;
		struct epoll_event * iEpollEvent; 
		for (n=0; n<numfd;n++){
			// if an incoming socket.
			iEpollEvent = m_epoll.get_event_by_id(n);
			if (iEpollEvent->data.fd == m_TCPSocket.get_socket_fd()){
				int32_t conn_sock = m_TCPSocket.accept_conn();

				std::cout << "new client connected ! \n";
				// add client to user map
				User new_user = {0};
				new_user.id = conn_sock;
				user_map[conn_sock] = new_user;
				
				// set non blocking 
				int flags = fcntl(conn_sock, F_GETFL, 0);
				if (fcntl(conn_sock, F_SETFL, flags | O_NONBLOCK) < 0){
					std::cout << "set non blocking failed \n";
				}
				m_epoll.epoll_add(conn_sock);
        
			// if incoming message	
			}else{	

				char recvbuf[BUFSIZE];
        		memset( recvbuf, '\0', BUFSIZE );

				if ( recv(iEpollEvent->data.fd, recvbuf,BUFSIZE,0) != 0) {
					if (!strcmp(recvbuf, "exit")) break;
            		fprintf(stderr,"[server] recv msg: %s\n", recvbuf);

					std::map<int32_t, User>::iterator iter;
    				iter = user_map.begin();

    				while(iter != user_map.end()) {
						send(iter->first, recvbuf, strlen(recvbuf), 0);
            			fprintf(stderr,"[server] send to: %d\n\n", iter->first);
        				iter++;
    				}
            		
    			}else{
					// if recv returns 0, close the connection and unregister the user
					m_epoll.epoll_close(conn_sock);
					user_map.erase(iEpollEvent->data.fd);
				}
				
			}	
		}

	}

	return 0;
}
