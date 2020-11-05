#include "MessageHead.h"

int main(){

    MessageHead mh, mh2;
    mh.m_Length = 10;
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    if ( mh.toBytes(buf) ==-1){
        printf ("failed!");
    }
    
    printf("bytes are: %x", *buf);

// 
    mh2.toClass(buf, sizeof(int32_t));
    printf("m2 mlength now is: %d", mh2.m_Length);
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
    memcpy(&m_Length, from_buffer, sizeof(int32_t));
    return 0;
}