/**
 *
 * File Name: include/kern/ctype.h
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

#ifndef ROCK64_KERN_CTYPE_H
#define ROCK64_KERN_CTYPE_H

extern int isalnum(const int c);
extern int isalpha(const int c);
extern int isblank(const int c);
extern int iscntrl(const int c);
extern int isdigit(const int c);
extern int isgraph(const int c);
extern int islower(const int c);
extern int isprint(const int c);
extern int ispunct(const int c);
extern int isspace(const int c);
extern int isupper(const int c);
extern int isxdigit(const int c);
extern int tolower(const int c);
extern int toupper(const int c);

#endif
