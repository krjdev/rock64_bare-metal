/**
 *
 * File Name: libkern/string/memcpy.c
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

#include <stdint.h>

void *memcpy(void *dst, const void *src, int len)
{
    int i;
    uint8_t *p_dst;
    uint8_t *p_src;
    
    p_dst = (uint8_t *) dst;
    p_src = (uint8_t *) src;
    
    for (i = 0; i < len; i++)
        p_dst[i] = p_src[i];
    
    return dst;
}
