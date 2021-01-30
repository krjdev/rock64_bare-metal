/**
 *
 * File Name: libc/unistd/read.c
 * Title    : C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-30
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

#include <syscall.h>
#include <unistd.h>
#include <errno.h>

ssize_t read(int fd, void *buf, size_t len)
{
    if ((fd == STDOUT_FILENO) || 
        (fd == STDERR_FILENO))  {
        errno = EBADF;
        return -1;
    }
    
    if (!buf) {
        errno = EINVAL;
        return -1;
    }
    
    return SYS_file_read(fd, buf, len);
}
