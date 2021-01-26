/**
 *
 * File Name: libkern/string/memcmp.c
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

int memcmp(const void *m1, const void *m2, int len)
{
    uint8_t *p1;
    uint8_t *p2;
    int i;
    
    p1 = (uint8_t *) m1;
    p2 = (uint8_t *) m2;
    
    for (i = 0; i < len; i++) {
        if (p1[i] != p2[i])
            return 1;
    }
    
    return 0;
}
