#include "Client/TCPClient.h"



int main(){

    TCPClient myClient;

    myClient.init();
    myClient.run();

    return 0;
}