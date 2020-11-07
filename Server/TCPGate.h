 
#include "../Protobuf/message.pb.h"
#include "../Commons/utils.h"
#include "../Commons/Serializer.h"


//

struct ServerInfo{
    ServerInfo(char* ipstr ,int32_t port) {
		this->ipstr=ipstr;
		this->port=port;
	};
    char* ipstr;
    int32_t port;
};

struct Clients{
	int32_t client_id;
    int32_t server_fd;
    char m_sendbuf[BUFFSIZE];
    char m_recvbuf[BUFFSIZE];
};

struct Servers{
    int32_t server_id;
    TCPSocket m_sock;
    char m_sendbuf[BUFFSIZE];
    char m_recvbuf[BUFFSIZE];
};

class TCPGate{

    public:
        TCPGate();
        ~TCPGate();
        void run();
        void init();
        void poll();
        void connect_servers(std::string conf_path);


    private:


    public:

    private:
        char m_sendbuf[BUFFSIZE];
        char m_recvbuf[BUFFSIZE];
        TCPSocket m_ClientsHanldeSocket;
        Epoll m_epoll;
        int32_t m_epoll_fd;
        struct epoll_event * m_epoll_event; 
        std::map<int32_t, Clients> m_clients;
        std::map<int32_t, Servers> m_servers;
        ServerInfo serverInfos[2] = {[0]=ServerInfo("127.0.0.1", 10009),[1]=ServerInfo("127.0.0.1", 10010)};
        Serializer m_Serializer;
        Logger m_Logger;

        
};