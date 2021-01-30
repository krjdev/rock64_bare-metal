/**
 *
 * File Name: libc/syscall.c
 * Title    : C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-25
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

#include <asm/syscall.h>
#include <syscall.h>

/* Process operations */
/* Exit normal */
void SYS_proc_exit(int code)
{
    asm_SYS_proc_exit(code);
}

/* Exit abnormal (abort function) */
void SYS_proc_abort(void)
{
    asm_SYS_proc_abort();
}

/* File operations */
/* Close file */
int SYS_file_close(int fd)
{
    return asm_SYS_file_close(fd);
}

/* Write to file */
ssize_t SYS_file_write(int fd, const void *buf, size_t len)
{
    return asm_SYS_file_write(fd, buf, len);
}

/* Read from file */
ssize_t SYS_file_read(int fd, void *buf, size_t len)
{
    return asm_SYS_file_read(fd, buf, len);
}

/* Synchronize file (flush buffers) */
int SYS_file_fsync(int fd)
{
    return asm_SYS_file_fsync(fd);
}
