/**
 *
 * File Name: libkern/string/strcmp.c
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

int strcmp(const char *s1, const char *s2)
{
    int i = 0;
    
    while (s1[i] != '\0') {
        if (s1[i] != s2[i])
            return 1;
        
        i++;
    }
    
    return 0;
}
