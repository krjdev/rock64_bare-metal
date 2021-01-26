/**
 *
 * File Name: libc/syscall.c
 * Title    : C Library
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

#include <stdint.h>
#include <stddef.h>

#include <asm/syscall.h>

void sys_exit(int nr)
{
    _sys_exit(nr);
}

int sys_open(const char *file, int flags)
{
    return sys_open(file, flags);
}

void sys_close(int fd)
{
    _sys_close(fd);
}

int sys_write(int fd, const uint8_t *buf, size_t len)
{
    return _sys_write(fd, buf, len);
}

int sys_read(int fd, uint8_t *buf, size_t len)
{
    return _sys_read(fd, buf, len);
}

void sys_sleep(int seconds)
{
    _sys_sleep(seconds);
}

void sys_abort(void)
{
    _sys_abort();
}
