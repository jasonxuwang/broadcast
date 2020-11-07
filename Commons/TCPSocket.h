
#ifndef _TCPSOCKET_
#define _TCPSOCKET_

#include "utils.h"

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
        
    private:
        

};

#endif