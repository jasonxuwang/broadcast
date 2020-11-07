
#include "../Protobuf/message.pb.h"
#include "../Commons/utils.h"
#include "../Commons/Serializer.h"

struct User{
	int32_t id;
    char m_sendbuf[BUFFSIZE];
    char m_recvbuf[BUFFSIZE];
};



class TCPServer{

    public:
        TCPServer();
        ~TCPServer();
        void run();
        void init();
        void poll();
    private:


    public:

    private:
        char m_sendbuf[BUFFSIZE];
        char m_recvbuf[BUFFSIZE];
        TCPSocket m_TCPSocket;
        Epoll m_epoll;
        int32_t m_epoll_fd;
        struct epoll_event * m_epoll_event; 
        std::map<int32_t, User> m_user_map;
        Serializer m_Serializer;
        Logger m_Logger;

        
};