/**
 *
 * File Name: libc/unistd/write.c
 * Title    : C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-26
 * Modified : 2021-01-30
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : ISC (see LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <syscall.h>
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t len)
{
    if (fd == STDIN_FILENO)
        return -1;
    
    return SYS_file_write(fd, buf, len);
}
