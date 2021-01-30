/**
 *
 * File Name: libc/stdio/putc.c
 * Title    : C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-27
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

#include <stddef.h>
#include <stream.h>
#include <stdio.h>

int putc(int c, struct _IO_FILE *stream)
{
    ssize_t ret;
    char buf[1];
    
    buf[0] = (char) c;
    ret = stream_write(stream, (const void *) buf, 1);
    
    if (ret == -1)
        return EOF;
    
    return (int) buf[0];
}
