/**
 *
 * File Name: libc/include/stream.h
 * Title    : C Library - Internal
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-30
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

#ifndef ROCK64_LIBC_STREAM_H
#define ROCK64_LIBC_STREAM_H

#include <stddef.h>

struct _IO_FILE {
    int fd;
};

struct _IO_FILE *stdin;
struct _IO_FILE *stdout;
struct _IO_FILE *stderr;

extern void stream_init(void);
extern ssize_t stream_write(struct _IO_FILE *stream, const void *buf, size_t len);
extern ssize_t stream_read(struct _IO_FILE *stream, void *buf, size_t len);

#endif
