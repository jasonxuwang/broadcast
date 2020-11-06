#ifndef _SERIALIZER_
#define _SERIALIZER_


#include <stdint.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <net/if.h>
#include <dirent.h>
#include <dlfcn.h>
#include <sys/select.h>
#include <assert.h>
#include <string>
#include <sys/epoll.h>
#include <map>
#include <iostream>
#define BUFSIZE 1024


#include "../Protobuf/message.pb.h"
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
        Message m_Message;
        char m_buffer[BUFSIZE];
        int32_t read(char* iBuffer, int32_t iSize);
        int32_t serialize(Message iMessage, char* iBuffer); // parse a message from the current buffer, set the message member;
        int32_t deserialize(); // 
        Message getMessage(); // return the member message;
        void reset();
        int32_t encode_int32(char *iBuff,  int32_t iMessageLength) ;
        int32_t decode_int32(char *iBuff) ;


    private:
        int32_t m_offset, m_MessageLength;



};


#endif