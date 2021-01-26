/**
 *
 * File Name: include/user/asm/syscall.h
 * Title    : Simple Standard C Library
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

#ifndef ROCK64_USER_ASM_SYSCALL_H
#define ROCK64_USER_ASM_SYSCALL_H

#include <stddef.h>
#include <stdint.h>

extern void _sys_exit(int code);
extern int _sys_open(const char *file, int flags);
extern void _sys_close(int fd);
extern int _sys_write(int fd, const uint8_t *buf, size_t len);
extern int _sys_read(int fd, uint8_t *buf, size_t len);
extern void _sys_sleep(int seconds);
extern void _sys_abort(void);

#endif
