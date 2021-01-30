/**
 *
 * File Name: asm/start.S
 * Title    : AArch64 Main entry point for User Application
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-29
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

#include <asm/asm.h>
#include <asm/syscall.h>

.text

ENTRY(_start)
__el0_enter:
    /* Zero BSS */
__el0_bss:
    ldr x0, =_user_bss_s
    ldr x1, =_user_bss_e
    sub x1, x1, x0
    mov x2, #0x0
    cbz x1, __el0_libc
__el0_bss_loop:
    strb w2, [x0], #1
    sub x1, x1, #1
    cbnz x1, __el0_bss_loop
    stp x29, x30, [sp, #-16]!
    mov x29, sp
__el0_libc_init:
    bl libc_init
__el0_main:
    bl main
__el0_libc_exit:
    bl libc_exit
    ldp x29, x30, [sp], #16
__el0_exit:
    mov x1, x0
    mov x0, #__SYS_PROC_EXIT
    svc #__SYS_PROC

.end
