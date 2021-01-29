/**
 *
 * File Name: asm/syscall.S
 * Title    : AArch64 Syscalls for Userland
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-29
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

#include <asm/asm.h>

.text

SYSCALL(_sys_exit)
    svc #0

SYSCALL(_sys_open)
    svc #1
    ret

SYSCALL(_sys_close)
    svc #2
    ret

SYSCALL(_sys_write)
    svc #3
    ret

SYSCALL(_sys_read)
    svc #4
    ret

SYSCALL(_sys_sleep)
    svc #5
    ret

SYSCALL(_sys_abort)
    svc #6

.end
