/**
 *
 * File Name: include/string.h
 * Title    : C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-29
 * Modified : 2021-01-30
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : ISC (see LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#ifndef ROCK64_STRING_H
#define ROCK64_STRING_H

/* Compare memory */
extern int memcmp(const void *m1, const void *m2, int len);
/* Copy memory */
extern void *memcpy(void *dst, const void *src, int len);
/* Set memory */
extern void *memset(void *buf, const int val, int len);

/* Concatenate strings */
extern char *strcat(char *dst, const char *src);
/* Compare strings */
extern int strcmp(const char *s1, const char *s2);
/* Copy string */
extern char *strcpy(char *dst, const char *src);
/* String length */
extern int strlen(const char *s);
/* Concatenate strings */
extern char *strncat(char *dst, const char *src, int num);
/* Compare strings */
extern int strncmp(const char *s1, const char *s2, int num);
/* Copy string */
extern char *strncpy(char *dst, const char *src, int num);

/* Return error description */
extern char *strerror(int errnum);

#endif
