/**
 * Suppose iBuffer is the starter of the buffer
 * return the length of message
 * */


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


// #include "message.pb.h"
#include "Epoll.h"
#include "TCPSocket.h"
#include "../Protobuf/message.pb.h"
#include "MessageHead.h"


int32_t get_message_len(char* iBuffer, int32_t iHeaderLength);

/**
 * Suppose iBuffer is the starter of the buffer
 * construct a message object
 * return the length of message.
 * */
int32_t get_message(char* iBuffer, int32_t iMessageLength, Message* iMessage );