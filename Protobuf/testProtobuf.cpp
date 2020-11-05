#include "message.pb.h"
#include <string>
#include <iostream>

int main(){
    Message mymsg;
    mymsg.set_from(0);
    mymsg.set_to(1);
    const char* charstr=  "hello world!";
    std::string str(charstr);
    mymsg.set_data(str);


    std::cout << mymsg.to() << "\n";
    std::cout << mymsg.from() << "\n";
    std::cout << mymsg.data() <<  "\n";

}