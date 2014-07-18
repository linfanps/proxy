#ifndef __PROXY_H
#define __PROXY_H

#include <pthread.h>
#include "config.h"
#include "global.h"
#include "packet.h"
#include "net.h"


typedef struct proxy_server_t {
    config_t *config;
    int listen_fd; /* 监听socket描述符号 */
    ulong thread_id; /* 全局thread_id 从1开始递增 */
    char default_charset_num; /* 默认的编码 */

} proxy_server_t;

typedef struct proxy_thread_t {
    int fd;
    char ip[MAX_IP_LEN];
    int port;
    ulong thread_id;
    short server_status;
    char scramble[SCRAMBLE_LENGTH+1];
    
    network_t *net;
    
} proxy_thread_t;

#endif
