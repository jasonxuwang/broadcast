#include "Server/TCPServer.h"


int main(int argc,char **argv){

    TCPServer myServer;

    if (argc < 2){
        std::cout << "Missing args. Usage: ./serv [port]\n";
        return -1;
    }
    myServer.init(atoi(argv[1]));
    myServer.run();

    return 0;
}