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
#include "../Commons/Epoll.h"
#include "../Commons/TCPSocket.h"
#include "../Protobuf/message.pb.h"
#include "../Commons/MessageHead.h"
#include "../Commons/utils.h"

#define BUFSIZE 1024

struct User{
	int32_t id;
};



class TCPServer{

    public:
        TCPServer();
        ~TCPServer();
        void run();
        void init();
        void poll();
        int32_t get_message(char* iBuffer, int32_t offset);
    private:


    public:

    private:
        char m_sendbuf[BUFSIZE];
        char m_recvbuf[BUFSIZE];
        TCPSocket m_TCPSocket;
        Epoll m_epoll;
        int32_t m_epoll_fd;
        struct epoll_event * m_epoll_event; 
        std::map<int32_t, User> m_user_map;
};