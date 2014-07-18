#include <errno.h>
#include "net.h"
#include "log.h"
#include "packet.h"


static int net_real_write(int fd, const uchar* packet, size_t len);
int net_write_buff(network_t *net, const uchar *packet, ulong len);
int net_flush(network_t *net);

static int create_socket()
{
    int fd;
    if (-1 == (fd = socket(AF_INET, SOCK_STREAM,0))) {
        log_(LOG_ERROR, "create socket failed, errno:%d, errmsg:%s", errno,strerror(errno));
        return PROXY_ERROR;
    }

    return fd;
}

int create_listen_socket(int port, int backlog)
{
    int fd = create_socket();
    if (PROXY_ERROR == fd) {
        log_(LOG_ERROR, "create listen socket failed");
        return fd;
    }
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (-1 == bind(fd, (struct sockaddr *)&addr, sizeof(addr))) {
        log_(LOG_ERROR, "bind listen socket failed, port %d, errno:%d, errmsg:%s", port, errno, strerror(errno));
        close(fd);
        return PROXY_ERROR;
    }
    
    if (-1 == listen(fd, backlog)) {
        log_(LOG_ERROR, "listen socket failed, backlog:%d, errno:%d, errmsg:%s", backlog, errno, strerror(errno));
        close(fd);
        return PROXY_ERROR;
    }
    return fd;
}
int waiting_for_client_to_connect(int fd, struct sockaddr *addr)
{
    socklen_t len = sizeof(*addr);
    int new_connection_fd;
    if (-1 == (new_connection_fd = accept(fd, addr, &len))) {
        if (EINTR == errno) {
            return ACCEPT_AGAIN;
        }
        log_(LOG_ERROR, "accept failed, fd:%d, errno:%d, errmsg:%d", fd, errno, strerror(errno));
        return PROXY_ERROR;
    }
    return new_connection_fd;
}
int net_write_packet(network_t *net, const uchar *packet, ulong len)
{
    uchar header[PACKET_HEADER_LEN];
    int3store(header, len);
    header[3] = (uchar)net->packet_num;

    int ret = net_write_buff(net, header, PACKET_HEADER_LEN) ||
                net_write_buff(net, packet, len) || 
                net_flush(net);
    return ret;

}
int net_write_buff(network_t *net, const uchar *packet, ulong len)
{
    ulong length_left = net->buff->size-net->buff->pos;
    if (len > length_left) {
        //Todo:
    }
    memcpy(net->buff->data, packet, len);
    net->buff->pos += len;
    return PROXY_OK;

}
int net_flush(network_t *net)
{
    int ret = PROXY_OK;
    if (net->buff->pos != net->buff->size) {
        ret = net_real_write(net->fd, net->buff->data, net->buff->size-net->buff->pos);
        net->buff->pos = 0; /* 清空 */
    }
    return ret;
    
}
static int net_real_write(int fd, const uchar* packet, size_t len)
{
    size_t write_len = 0;
    ssize_t ret;

    while (write_len != len) {
        ret = write(fd, packet, len-write_len);
        if (ret < 0) {
            if (errno == EINTR || errno == EAGAIN) {
                continue;
            } else {
                log_(LOG_ERROR, "write failed, fd:%d, errno:%d, errmsg:%d", fd, errno, strerror(errno));
                return PROXY_SOCKET_WRITE_ERROR;
            }
        } else if (ret == 0) {
                return PROXY_SOCKET_SHUTDOWN;
        } else {
            write_len += ret;
        }
    }

    return PROXY_OK;
}
