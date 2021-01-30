/**
 *
 * File Name: libc/stream.c
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

#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>
#include <stream.h>

void stream_init(void)
{
    stdin = NULL;
    stdout = NULL;
    stderr = NULL;
    
    stdin = (struct _IO_FILE *) malloc(sizeof(struct _IO_FILE));
    
    if (!stdin)
        abort();
    
    stdin->fd = STDIN_FILENO;
    
    stdout = (struct _IO_FILE *) malloc(sizeof(struct _IO_FILE));
    
    if (!stdout) {
        free(stdin);
        abort();
    }
    
    stdout->fd = STDOUT_FILENO;
    
    stderr = (struct _IO_FILE *) malloc(sizeof(struct _IO_FILE));
    
    if (!stderr) {
        free(stdin);
        free(stdout);
        abort();
    }
    
    stderr->fd = STDERR_FILENO;
}

ssize_t stream_write(struct _IO_FILE *stream, const void *buf, size_t len)
{
    if (!stream)
        return -1;
    
    return SYS_file_write(stream->fd, buf, len);
}

ssize_t stream_read(struct _IO_FILE *stream, void *buf, size_t len)
{
    if (!stream)
        return -1;
    
    return SYS_file_read(stream->fd, buf, len);
}
