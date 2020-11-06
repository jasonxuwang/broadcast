/**
 * Suppose iBuffer is the starter of the buffer
 * return the length of message
 * */

#include "utils.h"


// int32_t encode_int32(char *iBuff,  int32_t iMessageLength) {
//     char bytes[4];
//     bytes[0] = (iMessageLength>>24) & 0xFF;
//     bytes[1] = (iMessageLength>>16) & 0xFF;
//     bytes[2] = (iMessageLength>>8) & 0xFF;
//     bytes[3] = (iMessageLength) & 0xFF;
//     memcpy(iBuff, bytes, sizeof(bytes));
//     return sizeof(int32_t);
// }

// int32_t decode_int32(char *iBuff) {
//     int num = 0;
//     for (int i=0;i<4;i++){
//         num<<8;
//         num |= iBuff[i];
//     }
//     return num;
// }



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