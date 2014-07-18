#include "util.h"

/**
 * 从源字符串中拷贝n个字节到目标字符串中，若源字符串长度小n，则拷贝整个源字符串包括'\0'
 * 参数: dst 目标字符串，src 源字符串 n 拷贝字节数
 * 返回值: 指向目的字符串'\0'或(dst+n)的指针
 */
char *strnmov(register char *dst, register const char* src, size_t n)
{
    while (n--) {
        if (!(*dst++ = *src++)){
            return (char*)(dst-1);
        }
    }
    return dst;
}

/**
 * 从源字符串中拷贝n个字节到目标字符串中，并添加'\0',若源字符串长度小n，则拷贝整个源字符串包括'\0'
 * 参数: dst 目标字符串，src 源字符串 n 拷贝字节数
 * 返回值: 指向目的字符串'\0'的指针
 */
char *strmake(register char *dst, register const char* src, size_t n)
{
    while (n--) {
        if (!(*dst++ = *src++)){
            return (char*)(dst-1);
        }
    }
    *dst = '\0';
    return dst;
}
