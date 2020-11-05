#include "MessageHead.h"
#include <iostream>
#include <cstring>
int main(){

    MessageHead mh;
    mh.m_Length = 10;
    int outlen = 0;
    char* buf[1024];

    mh.toBytes(buf);

    printf("bytes are: %x",buf);
    return 0;
}


MessageHead::MessageHead(){

}

MessageHead::~MessageHead(){
    
}



int32_t MessageHead::toBytes(char* to_buffer){
        // convert the m_Length to its byte array presentation
        int32_t iRemainingLength = sizeof(to_buffer) - strlen(to_buffer);
        if (sizeof(m_Length) < iRemainingLength){
            return -1;
        }
        memcpy(to_buffer, &m_Length, sizeof(m_Length));
        return sizeof(m_Length);
}       

int32_t MessageHead::toClass(char* from_buffer, int32_t outputLength){
    if (outputLength < sizeof(int32_t) ){
            return -1;
    }

    memcpy(&m_Length, from_buffer, sizeof(int32_t));
    return 0;
}