/**
 * Suppose iBuffer is the starter of the buffer
 * return the length of message
 * */

#include "utils.h"


int32_t get_message_len(char* iBuffer, int32_t iHeaderLength){
    // if available chars even less than headerlength, return error
    if (strlen(iBuffer) < iHeaderLength){
        return -1;
    }

    // get message header from the initial chars
    MessageHead iMessageHead;
    iMessageHead.toClass(iBuffer, iHeaderLength);

    // now we have the length of message body;
    return iMessageHead.m_Length;
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
    iMessage.ParseFromArray(iBuffer, iMessageLength);
    return iMessageLength;
}