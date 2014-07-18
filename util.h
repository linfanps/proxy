#ifndef __UTIL_H_
#define __UTIL_H_

#include <sys/types.h>
char *strnmov(register char *dst, register const char* src, size_t n);
char *strmake(register char *dst, register const char* src, size_t n);

#endif
