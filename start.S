/**
 *
 * File Name: start.S
 * Title    : AArch64 Main Entry Point
 * Project  : 
 * Author   : Copyright (C) 2020 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2020-06-05
 * Modified : 2020-06-08
 * Revised  : 
 * Version  : 0.1.1.0
 * License  : ISC (see LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <asm.h>

IMPORT_C(kern_main)

.text

ENTRY(_start)
    /* Disable interrupts (IRQ and FIQ) */
    msr DAIFSet, #3
    
    /* Make sure CPU0 executes kern_main only, ... */
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #0
    beq L1
L0:
    /* ... all other CPU's wait forerver */
    wfe
    b L0
L1:
    /* Setup Stack Pointer */
    ldr x0, =_kern_stack_e
    mov sp, x0
    /* Clear BSS, if any */
    ldr x0, =_kern_bss_s
    ldr x1, =_kern_bss_e
    sub x1, x1, x0
    mov x2, #0x0
    cbz x1, L3
L2:
    strb w2, [x0], #1
    sub x1, x1, #1
    cbnz x1, L2
L3:
    bl kern_main
L4:
    /* Should never be reached, wait forerver */
    wfe
    b L4

.end
