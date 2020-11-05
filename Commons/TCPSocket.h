
#ifndef _TCPSOCKET_
#define _TCPSOCKET_


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
#define BUFSIZE 1024

class TCPSocket{


    public:
        TCPSocket();
        ~TCPSocket();

    private:
        int32_t m_socket_fd, addrlen;
        char recvbuf[BUFSIZE], sendbuf[BUFSIZE];
        struct sockaddr_in m_socket_addr;
	    struct sockaddr_in m_client_addr;

    public:
        int32_t as_server(int32_t port);
        int32_t as_client(char* ipstr,int32_t port);
        int32_t get_socket_fd();
        // wrapper for socket functions
        void clear_buff(char* iBuff);
        int32_t accept_conn();

        char m_recvbuf[BUFFSIZE];
        char m_sendbuf[BUFFSIZE];
        
    private:
        

};

#endif