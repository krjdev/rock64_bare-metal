/**
 *
 * File Name: kern/kern_panic.c
 * Title    : Kernel
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

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void kern_panic(const char *func, int err)
{
    puts("[PANIC]: Abort\r\n");
    puts(func);
    puts(": ");
    
    switch (err) {
    case EINVAL:
        puts("Invalid argument\r\n");
        break;
    case ENOMEM:
        puts("No memory (malloc)\r\n");
        break;
    case ENODEV:
        puts("Invalid device\r\n");
        break;
    case EIOERR:
        puts("I/O error\r\n");
        break;
    case ENODIR:
        puts("No such file or directory\r\n");
        break;
    default:
        puts("Unknown\r\n");
    }
    
    abort();
}
