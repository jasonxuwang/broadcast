


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


class Epoll{
    public:

    private:
        int32_t m_epoll_fd;
        int32_t m_timeout, m_max_event;
        struct epoll_event m_event;
        struct epoll_event* m_events;
    public:
        // constructors and destructors
        Epoll();
        ~Epoll();
        int32_t epoll_init(int32_t iTimeout, int32_t iMaxEvent);
        int32_t epoll_add(int32_t iSockFd);
        int32_t wait();
        int32_t get_epoll_fd();
        epoll_event* get_event_by_id(int32_t iId);
        int32_t epoll_close(int32_t iSockFd);
    private:



};