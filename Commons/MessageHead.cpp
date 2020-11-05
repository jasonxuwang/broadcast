#include "MessageHead.h"
#include <iostream>
#include <cstring>
int main(){

    MessageHead mh;
    mh.m_Length = 10;
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    if ( mh.toBytes(buf) ==-1){
        printf ("failed!");
    }
    

    printf("bytes are: %x", *buf);
    return 0;
}


MessageHead::MessageHead(){

}

MessageHead::~MessageHead(){
    
}



int32_t MessageHead::toBytes(char* to_buffer){
        // convert the m_Length to its byte array presentation
        printf("m_length is : %d",m_Length);
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