/**
 *
 * File Name: string.h
 * Title    : Minimalistic String Library
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

#ifndef STRING_H
#define STRING_H

extern void *memcpy(void *dst, void *src, int len);
extern void *memset(void *buf, int val, int len);

extern int strlen(const char *s);

#endif
