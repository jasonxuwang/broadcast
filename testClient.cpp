#include "Client/TCPClient.h"



int main(int argc,char **argv){

    TCPClient myClient;

    myClient.init(argv[1],argv[2]);
    myClient.run();

    return 0;
}