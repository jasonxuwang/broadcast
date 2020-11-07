#include "TCPSocket.h"

TCPSocket::TCPSocket(){
    
}


TCPSocket::~TCPSocket(){
    
}


int32_t TCPSocket::Accept(){
    return  accept(m_socket_fd, (struct sockaddr *) &m_client_addr, (socklen_t*) &addrlen);

}


int32_t TCPSocket::Socket(){
    m_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket_fd < 0){
        perror("tcp socket: socket creation failed");
        exit(EXIT_FAILURE);
    }
    return m_socket_fd;
}

int32_t TCPSocket::Listen(){
    if (listen(m_socket_fd, 20)!= 0){
        perror("tcp socket: listen failed");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int32_t TCPSocket::Bind(char* ipstr , int32_t port){

    memset(&m_socket_addr, 0, sizeof(m_socket_addr)); // empty memory
    m_socket_addr.sin_family = AF_INET; // set protocol

    m_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // currently treat it as any
    m_socket_addr.sin_port = (u_short)htons(port); // set port
    // socklen_t addr_size = socklen_t(sizeof(m_socket_addr)); // set addrsize
    if (bind(m_socket_fd,  (const sockaddr*) &m_socket_addr ,sizeof(m_socket_addr)) != 0) {
        perror("tcp socket: bind failed");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int32_t TCPSocket::Connect(char* ipstr , int32_t port){
    memset(&m_client_addr, 0, sizeof(m_client_addr)); // empty memory
	m_client_addr.sin_family = AF_INET; // set protocol
	m_client_addr.sin_port = htons(port); // set port
	inet_pton(AF_INET,ipstr,&m_client_addr.sin_addr.s_addr); // set ip address

    int res = connect(m_socket_fd,(struct sockaddr *)&m_client_addr,sizeof(m_client_addr));	
    if (res < 0){
        perror("tcp socket: connection failed");
        exit(EXIT_FAILURE);    
    }
    return 0;
}






int32_t TCPSocket::as_client(char* ipstr,int32_t port){
    // create a socket
    Socket();
    Connect(ipstr, port);
    return m_socket_fd;

    // m_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // if (m_socket_fd < 0){
    //     perror("tcp socket: socket creation failed");
    //     exit(EXIT_FAILURE);
    // }

    // // try to connect 
    // bzero(&m_client_addr,sizeof(m_client_addr));
	// m_client_addr.sin_family = AF_INET;
	// m_client_addr.sin_port = htons(port);
	// inet_pton(AF_INET,ipstr,&m_client_addr.sin_addr.s_addr); 

    // int res = connect(m_socket_fd,(struct sockaddr *)&m_client_addr,sizeof(m_client_addr));	
    // if (res < 0){
    //     perror("tcp socket: connection failed");
    //     exit(EXIT_FAILURE);    
    // }
}


int32_t TCPSocket::as_server(int32_t port){
    // create socket
    Socket();
    Bind( "INADDR_ANY" ,  PORT);
    Listen();
    return m_socket_fd;


    // m_socket_fd  = socket(AF_INET, SOCK_STREAM, 0);
    // if (m_socket_fd < 0){
    //     perror("tcp socket: socket creation failed");
    //     exit(EXIT_FAILURE);
    // }

    // // bind 
    // memset(&m_socket_addr, 0, sizeof(m_socket_addr)); // empty memory
    //     // set ip, port and size
    // m_socket_addr.sin_family = AF_INET;
    // m_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // m_socket_addr.sin_port = (u_short)htons(port);
    // socklen_t addr_size = socklen_t(sizeof(m_socket_addr));
    // if (bind(m_socket_fd,  (const sockaddr*) &m_socket_addr ,addr_size) != 0) {
    //     perror("tcp socket: bind failed");
    //     exit(EXIT_FAILURE);
    // }

    // // listen
    // if (listen(m_socket_fd, 20)!= 0){
    //     perror("tcp socket: listen failed");
    //     exit(EXIT_FAILURE);
    // }
    return m_socket_fd;
}




int32_t TCPSocket::get_socket_fd(){
    return m_socket_fd;
}





