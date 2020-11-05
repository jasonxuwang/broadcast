#include "MessageHead.h"
#include <iostream>
#include <cstring>
int main(){

    MessageHead mh;
    mh.m_Length = 10;
    int buflen = [1];
    char test[100];
    memcpy(test, buflen, sizeof(buflen));
    mh.toBytes(test, buflen);

    std::cout << "int bytes are :" <<test << std::endl;
    return 0;
}


MessageHead::MessageHead(){

}

MessageHead::~MessageHead(){
    
}



int32_t MessageHead::toBytes(char* to_buffer, int32_t& outputLength){
        if (outputLength < sizeof(int32_t) ){
            return -1;
        }



                
        char* a_begin = reinterpret_cast<char*>(m_Length);
        char* a_end = a_begin +4;
        copy(a_begin,a_end, back_inserter(chars));
        std::cout <<converted << "is converted! \n";
        std::copy(converted, converted+sizeof(converted), to_buffer);
        outputLength -= sizeof(converted);
        
        return 0;
}

int32_t MessageHead::toClass(char* from_buffer, int32_t outputLength){
    if (outputLength < sizeof(int32_t) ){
            return -1;
    }
    memcpy(&m_Length, from_buffer, sizeof(int32_t));
    return 0;
}