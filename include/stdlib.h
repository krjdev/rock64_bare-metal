/**
 *
 * File Name: include/stdlib.h
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

#ifndef ROCK64_STDLIB_H
#define ROCK64_STDLIB_H

#include <stddef.h>

#ifndef NULL
#define NULL    ((void *)0)
#endif

/* Process functions */
extern void abort(void);
extern void exit(int code);

/* Memory allocation functions */
extern void *malloc(size_t len);
extern void *realloc(void *ptr, size_t len);
extern void free(void *ptr);

/* Conversion functions */
extern int atoi(const char *s);
extern long int atol(const char *s);

#endif
