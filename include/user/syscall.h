/**
 *
 * File Name: include/user/syscall.h
 * Title    : C Library
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

#ifndef ROCK64_USER_SYSCALL_H
#define ROCK64_USER_SYSCALL_H

#include <stdint.h>
#include <stddef.h>

extern void sys_exit(int nr);
extern int sys_open(const char *file, int flags);
extern void sys_close(int fd);
extern int sys_write(int fd, const uint8_t *buf, size_t len);
extern int sys_read(int fd, uint8_t *buf, size_t len);
extern void sys_sleep(int seconds);
extern void sys_abort(void);

#endif
