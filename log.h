#ifndef __LOG_H
#define __LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include "global.h"

#define LOG_DEBUG 1
#define LOG_NOTICE 2
#define LOG_INFO 4
#define LOG_WARNING 8
#define LOG_ERROR 16


int init_logger_handler(const char *logpath, int level);
void log_(int level, const char *fmt, ...);

#endif
