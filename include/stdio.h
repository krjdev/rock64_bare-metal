/**
 *
 * File Name: include/stdio.h
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

#ifndef ROCK64_STDIO_H
#define ROCK64_STDIO_H

struct _IO_FILE;

extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;

typedef struct _IO_FILE FILE;

#ifndef EOF
#define EOF    (-1)
#endif

extern int puts(const char *s);
extern int putc(int c, FILE *stream);
extern int putchar(int c);

#endif
