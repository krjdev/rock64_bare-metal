/**
 *
 * File Name: libc/stdlib/realloc.c
 * Title    : Simple Standard C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-16
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
#include <string.h>

#include "heap.h"

void *realloc(void *ptr, int len)
{
    int size;
    void *p;
    
    if (!ptr)
        return NULL;
    
    if (len < 1)
        return NULL;
    
    size = heap_size(ptr);
    
    if (!size)
        return NULL;
    
    p = heap_alloc(len);
    
    if (!p)
        return NULL;
    
    memcpy(p, ptr, size);
    return p;
}
