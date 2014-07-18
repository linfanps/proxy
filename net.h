#ifndef __NET_H
#define __NET_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "global.h"

typedef struct byte_array_t {
    uchar *data;
    ulong size;
    ulong pos;
} byte_array_t;

typedef struct network_t {
    int fd;
    byte_array_t *buff;
    int packet_num;
} network_t;

int create_listen_socket(int port, int backlog);
int waiting_for_client_to_connect(int fd, struct sockaddr *addr);
int net_write_packet(network_t *net, const uchar *packet, ulong len);
#endif
