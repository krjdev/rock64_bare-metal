/**
 *
 * File Name: libc/string/strcat.c
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

char *strcat(char *dst, const char *src)
{
    int i = 0;
    int j = 0;
    
    while (dst[i] != '\0')
        i++;
    
    while (src[j] != '\0') {
        dst[i] = src[j];
        i++;
        j++;
    }
    
    dst[i] = '\0';
    return dst;
}
