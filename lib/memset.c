/**
 *
 * File Name: lib/memset.c
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

void *memset(void *buf, int val, int len)
{
    int i;
    unsigned char *p;
    
    p = (unsigned char *) buf;
    
    for (i = 0; i < len; i++)
        p[i] = (unsigned char) val;
    
    return buf;
}
