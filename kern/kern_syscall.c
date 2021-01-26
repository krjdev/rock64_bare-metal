/**
 *
 * File Name: kern/kern_syscall.c
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

#include <errno.h>
#include <stdio.h>

#include <kern/vfs.h>
#include <kern/panic.h>

void kern_syscall_exit(int code)
{
    puts("SYS_EXIT\r\n");
    kern_panic(__func__, 0);
}

int kern_syscall_open(const char *file, int flags)
{
    puts("SYS_OPEN\r\n");
    kern_panic(__func__, 0);
}

void kern_syscall_close(int fd)
{
    puts("SYS_CLOSE\r\n");
    kern_panic(__func__, 0);
}

int kern_syscall_write(int fd, const uint8_t *buf, int len)
{
    return kern_vfs_write(fd, buf, len);
}

int kern_syscall_read(int fd, uint8_t *buf, int len)
{
    return kern_vfs_read(fd, buf, len);
}

void kern_syscall_sleep(int seconds)
{
    puts("SYS_SLEEP\r\n");
    kern_panic(__func__, 0);
}

void kern_syscall_abort(void)
{
    puts("SYS_ABORT\r\n");
    kern_panic(__func__, 0);
}

void kern_syscall_unknown(void)
{
    puts("SYS_UNKNOWN\r\n");
    kern_panic(__func__, 0);
}

int kern_syscall_init(void)
{
    return ESUCCESS;
}
