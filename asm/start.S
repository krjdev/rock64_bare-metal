/**
 *
 * File Name: asm/start.S
 * Title    : AArch64 Main entry point for Uaserland
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

ENTRY(_start_user)
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
__el0_libc:
    bl libc_init
    bl main
    ldp x29, x30, [sp], #16
__el0_exit:
    svc #0

.end
