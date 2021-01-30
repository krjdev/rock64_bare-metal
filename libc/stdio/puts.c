/**
 *
 * File Name: libc/stdio/puts.c
 * Title    : C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-25
 * Modified : 2021-01-30
 * Revised  : 
 * Version  : 0.1.0.1
 * License  : ISC (see LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <string.h>
#include <stream.h>
#include <stddef.h>
#include <stdio.h>

int puts(const char *str)
{
    ssize_t ret;
    
    ret = stream_write(stdout, (const void *) str, strlen(str));
    
    if (ret == -1)
        return EOF;
    
    return (int) ret;
}
