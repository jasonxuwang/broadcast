#include "Client/TCPClient.h"



int main(int argc,char **argv){

    TCPClient myClient;

    if (argc < 3){
        std::cout << "Missing args. Usage: ./cli [ip] [port]\n";
        return -1;
    }
    myClient.init(argv[1],atoi(argv[2]));
    myClient.run();

    return 0;
}