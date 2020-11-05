#include "TCPSocket.h"

TCPSocket::TCPSocket(){
    
}


TCPSocket::~TCPSocket(){
    
}

int32_t TCPSocket::as_client(char* ipstr,int32_t port){
    // create a socket
    m_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket_fd < 0){
        perror("tcp socket: socket creation failed");
        exit(EXIT_FAILURE);
    }
    // try to connect 
    bzero(&m_client_addr,sizeof(m_client_addr));
	m_client_addr.sin_family = AF_INET;
	m_client_addr.sin_port = htons(port);
	inet_pton(AF_INET,ipstr,&m_client_addr.sin_addr.s_addr); 

    int res = connect(m_socket_fd,(struct sockaddr *)&m_client_addr,sizeof(m_client_addr));	
    if (res < 0){
         perror("tcp socket: connection failed");
        exit(EXIT_FAILURE);    
    }
	std::cout << "[client] connected to the server !!! \n";
}


int32_t TCPSocket::as_server(int32_t port){
    // create socket
    m_socket_fd  = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket_fd < 0){
        perror("tcp socket: socket creation failed");
        exit(EXIT_FAILURE);
    }

    // bind 

	addrlen = 0;
    memset(&m_socket_addr, 0, sizeof(m_socket_addr)); // empty memory
        // set ip, port and size
    m_socket_addr.sin_family = AF_INET;
    m_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_socket_addr.sin_port = (u_short)htons(port);
    socklen_t addr_size = socklen_t(sizeof(m_socket_addr));
    if (bind(m_socket_fd,  (const sockaddr*) &m_socket_addr ,addr_size) != 0) {
        perror("tcp socket: bind failed");
        exit(EXIT_FAILURE);
    }

    // listen
    if (listen(m_socket_fd, 20)!= 0){
        perror("tcp socket: listen failed");
        exit(EXIT_FAILURE);
    }
	
    return m_socket_fd;
}

int32_t TCPSocket::accept_conn(){
    return  accept(m_socket_fd, (struct sockaddr *) &m_client_addr, (socklen_t*) &addrlen);

}
int32_t TCPSocket::get_socket_fd(){
    return m_socket_fd;
}





