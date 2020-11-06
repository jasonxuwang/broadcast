#include "Server/TCPServer.h"

int main(){

    TCPServer myServer;

    myServer.init();
    myServer.run();

    return 0;
}