#include "MessageHead.h"


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