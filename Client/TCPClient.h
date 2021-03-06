
#include "../Protobuf/message.pb.h"
#include "../Commons/utils.h"
#include "../Commons/Serializer.h"


struct User{
	int32_t id;
};



class TCPClient{

    public:
        TCPClient();
        ~TCPClient();
        void init(char* ipstr,int32_t port);
        void poll();
        void run();
    private:


    public:

    private:
        int32_t m_id;
        char m_sendbuf[BUFFSIZE];
        char m_recvbuf[BUFFSIZE];
        TCPSocket m_TCPSocket;
        Serializer m_Serializer;
        Epoll m_epoll;
        int32_t m_epoll_fd;
        struct epoll_event * m_epoll_event; 

};