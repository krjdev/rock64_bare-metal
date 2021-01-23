/**
 *
 * File Name: libc/string/strncmp.c
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

int strncmp(const char *s1, const char *s2, int num)
{
    int i;
    
    for (i = 0; i < num; i++) {
        if (s1[i] != s2[i])
            return 1;
    }
    
    return 0;
}
