/**
 *
 * File Name: libc/stdlib/atol.c
 * Title    : Simple Standard C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-26
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

#include <string.h>
#include <ctype.h>

long int atol(const char *s)
{
    int len;
    int i;
    int sign = 0;
    long int ret = 0;
    long int tmp;
    long int mul = 1;
    
    if (!s)
        return 0;
    
    len = strlen(s);
    
    if (s[0] == '-') {
        sign = 1;
        len--;
    }
    
    for (i = len; i >= 0; i--) {
        if (isdigit(s[i])) {
            tmp = s[i] - '0';
            tmp *= mul;
            ret += tmp;
            mul *= 10;
            
        } else
            return 0;
    }
    
    if (sign) {
        ret--;
        ret = ~ret;
    }
    
    return ret;
}
