/**
 *
 * File Name: asm/syscall_kern.S
 * Title    : AArch64 Kernel Syscalls
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

#include <asm/asm.h>

IMPORT_C(kern_syscall_exit)
IMPORT_C(kern_syscall_open)
IMPORT_C(kern_syscall_close)
IMPORT_C(kern_syscall_write)
IMPORT_C(kern_syscall_read)
IMPORT_C(kern_syscall_sleep)
IMPORT_C(kern_syscall_abort)
IMPORT_C(kern_syscall_unknown)

.text

FUNCTION(_sys_exit)
    ldp x0, x1, [sp]
    bl kern_syscall_exit
    ret

FUNCTION(_sys_open)
    ldp x0, x1, [sp]
    bl kern_syscall_open
    ret

FUNCTION(_sys_close)
    ldp x0, x1, [sp]
    bl kern_syscall_close
    ret

FUNCTION(_sys_write)
    ldp x0, x1, [sp]
    ldp x2, x3, [sp, #16]
    bl kern_syscall_write
    ret

FUNCTION(_sys_read)
    ldp x0, x1, [sp]
    ldp x2, x3, [sp, #16]
    bl kern_syscall_read
    ret

FUNCTION(_sys_sleep)
    ldp x0, x1, [sp]
    bl kern_syscall_sleep
    ret

FUNCTION(_sys_abort)
    bl kern_syscall_abort
    ret

FUNCTION(_sys_unknown)
    bl kern_syscall_unknown
    ret

.end
