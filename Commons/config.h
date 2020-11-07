
#include <stdint.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>

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
#include <net/if.h>
#include <dirent.h>
#include <dlfcn.h>
#include <sys/select.h>
#include <assert.h>
#include <string>
#include <sys/epoll.h>
#include <map>
#include <iostream>
#include <fstream>



#include "Epoll.h"
#include "TCPSocket.h"
#include "../Protobuf/message.pb.h"
#include "Logger.h"


#define IPSTR "127.0.0.1"
#define PORT 10009

#define TIMEOUT 1000
#define MAXEVENT 100
#define BUFFSIZE 1024*8

#define LOG_FOLDER "./logs/"
#define LOG_PRINT_ABOVE -1 // print every thing above
#define LOG_SAVE_ABOVE 0 // only log level > INFO


