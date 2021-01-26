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
    ldp x0, x1, [sp, #16]
    stp x29, x30, [sp, #-16]!
    bl kern_syscall_exit
    ldp x29, x30, [sp], #16
    ret

FUNCTION(_sys_open)
    ldp x0, x1, [sp, #16]
    stp x29, x30, [sp, #-16]!
    bl kern_syscall_open
    ldp x29, x30, [sp], #16
    ret

FUNCTION(_sys_close)
    ldp x0, x1, [sp, #16]
    stp x29, x30, [sp, #-16]!
    bl kern_syscall_close
    ldp x29, x30, [sp], #16
    ret

FUNCTION(_sys_write)
    ldp x0, x1, [sp, #16]
    ldp x2, x3, [sp, #32]
    stp x29, x30, [sp, #-16]!
    bl kern_syscall_write
    ldp x29, x30, [sp], #16
    ret

FUNCTION(_sys_read)
    ldp x0, x1, [sp, #16]
    ldp x2, x3, [sp, #32]
    stp x29, x30, [sp, #-16]!
    bl kern_syscall_read
    ldp x29, x30, [sp], #16
    ret

FUNCTION(_sys_sleep)
    ldp x0, x1, [sp, #16]
    stp x29, x30, [sp, #-16]!
    bl kern_syscall_sleep
    ldp x29, x30, [sp], #16
    ret

FUNCTION(_sys_abort)
    stp x29, x30, [sp, #-16]!
    bl kern_syscall_abort
    ldp x29, x30, [sp], #16
    ret

FUNCTION(_sys_unknown)
    stp x29, x30, [sp, #-16]!
    bl kern_syscall_unknown
    ldp x29, x30, [sp], #16
    ret

.end
