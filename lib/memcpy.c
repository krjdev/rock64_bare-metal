/**
 *
 * File Name: lib/memcpy.c
 * Title    : String Library
 * Project  : 
 * Author   : Copyright (C) 2020 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2020-06-05
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

void *memcpy(void *dst, void *src, int len)
{
    int i;
    unsigned char *p_dst;
    unsigned char *p_src;
    
    p_dst = (unsigned char *) dst;
    p_src = (unsigned char *) src;
    
    for (i = 0; i < len; i++)
        p_dst[i] = p_src[i];
    
    return dst;
}
