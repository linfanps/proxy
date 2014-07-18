#include "log.h"
#include "proxy.h"

typedef struct logger_t {
    int fd;
    int level;
} logger_t;

static logger_t *logger = NULL;
static char *get_log_level_string(int level)
{
    switch (level) {
        case LOG_DEBUG: return "DEBUG";
        case LOG_NOTICE: return "NOTICE";
        case LOG_INFO: return "INFO";
        case LOG_WARNING: return "WARNING";
        case LOG_ERROR: return "ERROR";
        default : return "UNKONWN";
    }
}
int init_logger_handler(const char *log_path, int level)
{
    logger = (logger_t*)malloc(sizeof(logger_t));
    if (!logger) {
        printf("malloc logger failed\n");
        return -1;
    }

    if (-1 == (logger->fd = open(log_path, O_RDWR | O_APPEND | O_CREAT, S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR))) {
        printf("open log file failed\n");
        return -1;
    }

    logger->level = level;

    return 0;

}
static void log_it(const char *msg, int level)
{
   struct timeval tv;
   gettimeofday(&tv,0);
   struct tm *now = localtime(&tv.tv_sec);

   char buf[MAX_LOGMSG_LEN+MAX_LOGEXTRA_LEN]; 
   snprintf(buf,MAX_LOGMSG_LEN+MAX_LOGEXTRA_LEN, "[%4d-%02d-%02d %02d:%02d:%02d.%06ld][%s] %s\n", now->tm_year+1900,now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, tv.tv_usec, get_log_level_string(level), msg);

   if (-1 == write(logger->fd, buf, strlen(buf))) {
       printf("write log failed\n");
   }
}

void log_(int level, const char *fmt, ...)
{
   if (!logger) {
       printf("logger handler has not been initialized\n");
       return ;
   }
   if (0 == (logger->level & level)) {
       return ;
   }
   char msg[MAX_LOGMSG_LEN];
   va_list ap;
   va_start(ap, fmt);
   vsnprintf(msg, MAX_LOGMSG_LEN, fmt, ap);
   va_end(ap);
   log_it(msg, level);
}

