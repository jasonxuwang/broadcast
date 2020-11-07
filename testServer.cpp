#include "Server/TCPServer.h"


Logger logger;
logger.setfile("server.log");


int main(){

    TCPServer myServer;

    myServer.init();
    myServer.run();

    return 0;
}