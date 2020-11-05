#include "MessageHead.h"
#include <iostream>
#include <cstring>
int main(){

    MessageHead mh;
    mh.m_Length = 10;
    int outlen = 0;
    char* buf[1024];

    mh.toBytes(buf, &outlen);

    printf("bytes are: %x",buf);
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
        // convert the m_Length to its byte array presentation
        memcpy(to_buffer, m_Length, sizeof(m_Length));
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