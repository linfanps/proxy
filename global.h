#ifndef __GLOBAL_H
#define __GLOBAL_H

#define MAX_LOGMSG_LEN 1024
#define MAX_LOGEXTRA_LEN 512

#define PROXY_OK 0
#define PROXY_FATAL_ERROR -1
#define PROXY_ERROR -2

#define PROXY_SOCKET_WRITE_ERROR -201
#define PROXY_SOCKET_READ_ERROR -202
#define PROXY_SOCKET_SHUTDOWN -203
#define ACCEPT_AGAIN -101

#define MAX_IP_LEN 16


typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
#endif
