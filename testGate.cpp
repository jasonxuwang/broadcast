#include "Server/TCPGate.h"


int main(){

    TCPGate myGate;

    myGate.init();
    myGate.run();

    return 0;
}