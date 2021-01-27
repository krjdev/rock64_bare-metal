/**
 *
 * File Name: libc/stdio/putc.c
 * Title    : C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-27
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

#include <stdint.h>
#include <unistd.h>

int putc(const char c)
{
    uint8_t buf[1];
    
    buf[0] = (uint8_t) c;
    return write(1, buf, 1);
}
