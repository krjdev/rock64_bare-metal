/**
 *
 * File Name: include/kern/string.h
 * Title    : Kernel Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-25
 * Modified : 
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : ISC (see LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#ifndef ROCK64_KERN_STRING_H
#define ROCK64_KERN_STRING_H

extern int memcmp(const void *m1, const void *m2, int len);
extern void *memcpy(void *dst, const void *src, int len);
extern void *memset(void *buf, const int val, int len);
extern char *strcat(char *dst, const char *src);
extern int strcmp(const char *s1, const char *s2);
extern char *strcpy(char *dst, const char *src);
extern int strlen(const char *s);
extern char *strncat(char *dst, const char *src, int num);
extern int strncmp(const char *s1, const char *s2, int num);
extern char *strncpy(char *dst, const char *src, int num);

#endif
