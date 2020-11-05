/**
 * Suppose iBuffer is the starter of the buffer
 * return the length of message
 * */

#include "utils.h"

int32_t encode_int32(char **pOut,  uint32_t Src) {
    if (NULL == pOut || NULL == *pOut) {
        return 0;
    }

    *(uint32_t*)(*pOut) = htonl(Src);
    *pOut += sizeof(uint32_t);
    return int32_t(sizeof(uint32_t));
}

int32_t decode_int32(char **pIn,  uint32_t *pOut) {
    if (NULL == pIn || NULL == *pIn || NULL == pOut) {
        return 0;
    }
    *pOut = (uint32_t) ntohl((uint32_t)*(uint32_t*)(*pIn));
    *pIn += sizeof(uint32_t);
    return int32_t(sizeof(uint32_t));
}


int32_t get_message_len(char* iBuffer, int32_t iHeaderLength){
    // if available chars even less than headerlength, return error
    if (strlen(iBuffer) < iHeaderLength){
        return -1;
    }
    int32_t iMessageLength;
    memcpy(&iMessageLength, iBuffer, sizeof(int32_t));
    return iMessageLength;

    // // get message header from the initial chars
    // MessageHead iMessageHead;
    // iMessageHead.toClass(iBuffer, iHeaderLength);

    // // now we have the length of message body;
    // return iMessageHead.m_Length;
}


/**
 * Suppose iBuffer is the starter of the buffer
 * construct a message object
 * return the length of message.
 * */
int32_t get_message(char* iBuffer, int32_t iMessageLength, Message* iMessage ){
    if (strlen(iBuffer) < iMessageLength){
        return -1;
    }
    iMessage->ParseFromArray(iBuffer, iMessageLength);
    return iMessageLength;
}