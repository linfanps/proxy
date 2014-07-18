#include <stdio.h>
#include <stdlib.h>
#include "proxy.h"
#include "log.h"

proxy_server_t proxy_server;

static int init_proxy_server()
{
    if (NULL == (proxy_server.config = init_proxy_config("config"))) {
        log_(LOG_ERROR, "init proxy config error");
        return PROXY_FATAL_ERROR;
    }
    
    proxy_server.listen_fd = -1;
    proxy_server.thread_id = 1L;
    proxy_server.default_charset_num = 33;
    return PROXY_OK;

}
static int do_connection(proxy_thread_t* proxy_thread)
{
    
}
/* 线程执行函数*/
static void *handle_one_connection(void *arg)
{
   proxy_thread_t *proxy_thread = (proxy_thread_t*)arg;
    proxy_thread->id = pthread_self();
   log_(LOG_INFO, "client %s:%d is handled by thread %d",  proxy_thread->ip,  proxy_thread->port, (unsigned int) proxy_thread->thread_id);
   pthread_exit(0);
}
static int  get_handle_thread(proxy_thread_t *arg)
{
    pthread_t thread_do;
    int error;
    if (0 != (error = pthread_create(&thread_do, NULL, handle_one_connection, (void *)arg))) {
        log_(LOG_ERROR, "create handle thread failed, errno:%d, errmsg:%s", error, strerror(error));
        return PROXY_ERROR;
    }
    return PROXY_OK;
}
static void handle_client_connection()
{
    int client_socket;
    struct sockaddr_in client_addr;
    proxy_thread_t * proxy_thread;
    while (1) {
        log_(LOG_DEBUG, "waitting for client to connect");
        client_socket = waiting_for_client_to_connect(proxy_server.listen_fd, (struct sockaddr*)&client_addr);        
        if (ACCEPT_AGAIN == client_socket) {
            log_(LOG_INFO, "accept has been interrupted by signal");
            continue;
        }
        if (PROXY_ERROR == client_socket) {
            log_(LOG_ERROR, "handle connection failed");
            exit(-1);
        }
        proxy_thread = ( proxy_thread_t*)malloc(sizeof( proxy_thread_t)); 
        if (NULL ==  proxy_thread) {
            log_(LOG_ERROR, " proxy_thread malloc failed");
            exit(-1);
        }
        log_(LOG_INFO, "client %s:%d connect to server", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        proxy_thread->port = ntohs(client_addr.sin_port);
        proxy_thread->fd = client_socket;
        snprintf(proxy_thread->ip, MAX_IP_LEN, "%s", inet_ntoa(client_addr.sin_addr));
        
        get_handle_thread(proxy_thread);
    }
}
int main(int argc, char **argv)
{
    if (PROXY_OK != init_proxy_server()) {
        printf("init proxy_server failed\n");
        exit(1);
    }
    init_logger_handler("log/proxy.log", proxy_server.config->log_level); 

    if (PROXY_ERROR == (proxy_server.listen_fd = create_listen_socket(proxy_server.config->port, proxy_server.config->backlog))) {
        printf("init listen socket failed\n");
        exit(-1);
    }
    log_(LOG_DEBUG, "init listen socket success, port:%d, backlog:%d", proxy_server.config->port, proxy_server.config->backlog);

    handle_client_connection();
    return 0;
}

