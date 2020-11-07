#include "Server/TCPServer.h"


int main(int argc,char **argv){

    TCPServer myServer;

    myServer.init(atoi(argv[1]));
    myServer.run();

    return 0;
}