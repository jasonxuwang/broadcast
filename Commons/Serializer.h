#ifndef _SERIALIZER_
#define _SERIALIZER_


#include <stdint.h>


#include "../Protobuf/Status.pb.h"
#include "../Commons/utils.h"

/**
 * Serialize buffered 
 * 
 * 
 */

class Serializer{
    public:
        Serializer();
        ~Serializer();

        //
        Status m_Message;
        char m_buffer[BUFFSIZE];
        int32_t read(char* iBuffer, int32_t iSize);
        int32_t serialize(Status iMessage, char* iBuffer); // parse a message from the current buffer, set the message member;
        int32_t deserialize(); // 
        Status getMessage(); // return the member message;
        void reset();
        int32_t encode_int32(char *iBuff,  int32_t iMessageLength) ;
        int32_t decode_int32(char *iBuff) ;


    private:
        int32_t m_offset, m_MessageLength;



};


#endif