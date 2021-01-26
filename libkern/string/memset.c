/**
 *
 * File Name: libkern/string/memset.c
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

void *memset(void *buf, const int val, int len)
{
    int i;
    uint8_t *p;
    
    p = (uint8_t *) buf;
    
    for (i = 0; i < len; i++)
        p[i] = (uint8_t) val;
    
    return buf;
}
