/**
 *
 * File Name: start.S
 * Title    : AArch64 Main Entry Point
 * Project  : 
 * Author   : Copyright (C) 2020 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2020-06-05
 * Modified : 2020-06-07
 * Revised  : 
 * Version  : 0.1.0.2
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
    
    /* Make sure CPU0 executes kern_main only. ... */
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #0
    beq L1
L0:
    /* ... All other CPU's wait forerver */
    wfe
    b L0
L1:
    ldr x0, =_kern_stack_e
    mov sp, x0
    b kern_main
L2:
    /* Should never be reached, wait forerver */
    wfe
    b L2

.end
