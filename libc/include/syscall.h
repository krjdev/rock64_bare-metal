/**
 *
 * File Name: libc/include/syscall.h
 * Title    : C Library - Internal
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

#ifndef ROCK64_LIBC_SYSCALL_H
#define ROCK64_LIBC_SYSCALL_H

#include <stdint.h>
#include <stddef.h>

/* Process operations */
/* Exit normal */
extern void SYS_proc_exit(int code);
/* Exit abnormal (abort function) */
extern void SYS_proc_abort(void);
/* Allocate memory */
extern void *SYS_proc_alloc(size_t len, int flags);

/* File operations */
/* Close file */
extern int SYS_file_close(int fd);
/* Write to file */
extern ssize_t SYS_file_write(int fd, const void *buf, size_t len);
/* Read from file */
extern ssize_t SYS_file_read(int fd, void *buf, size_t len);
/* Synchronize file (flush buffers) */
extern int SYS_file_fsync(int fd);


#endif
