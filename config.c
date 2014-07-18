#include "config.h"
#include "log.h"

config_t* init_proxy_config(char *config_path)
{
    config_t *config = (config_t *)malloc(sizeof(config_t));
    if (config == NULL) {
        log_(LOG_ERROR, "config_t config malloc failed");
        return NULL;
    }

    config->port = 8888;
    config->backlog = 20;
    config->log_level = LOG_INFO | LOG_WARNING | LOG_ERROR;

    return config;
}

