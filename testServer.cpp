#include "Server/TCPServer.h"


int main(int argc,char **argv){

    TCPServer myServer;

    myServer.init();
    m_TCPSocket.as_server(atoi(argv[1]));
    m_epoll_fd  = m_epoll.epoll_init(TIMEOUT,MAXEVENT);
    m_epoll.epoll_add(m_TCPSocket.get_socket_fd());
    m_Serializer.reset();
    m_Logger.setfile("/Server/server.log");
    myServer.run();

    return 0;
}