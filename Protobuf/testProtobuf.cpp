#include <message.pb.h>

int main(){
    Message mymsg;
    mymsg.set_from(0);
    mymsg.set_to(1);
    string str = "hello world!";
    mymsg.set_data(str);
}