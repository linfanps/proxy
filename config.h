#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdio.h>
#include <stdlib.h>

typedef struct config_t {
    int log_level;
    int port;
    int backlog;
} config_t;


config_t *init_proxy_config(char *config_path);
#endif
