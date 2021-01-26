/**
 *
 * File Name: include/user/stdlib.h
 * Title    : C Library
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

#ifndef ROCK64_USER_STDLIB_H
#define ROCK64_USER_STDLIB_H

#include <stddef.h>

#ifndef NULL
#define NULL    ((void *)0)
#endif

extern int atoi(const char *s);
extern void abort(void);
extern void free(void *ptr);
extern void *malloc(size_t len);
extern void *realloc(void *ptr, size_t len);

#endif
