/**
 *
 * File Name: asm/vector.S
 * Title    : AArch64 Interrupt Vector Table
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-23
 * Modified : 
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : ISC (see file LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <asm.h>

IMPORT_C(exce_handler)
IMPORT_C(intr_handler)

.section .isr_vector

/* TODO: Vector table EL3 */
.balign 0x800
_vec_tbl_el3_s:
_vec_tbl_el3_cur_sp0:
/* Synchronous Abort */
_vec_tbl_el3_cur_sp0_syn:
    eret
.balign 0x80
/* IRQ */
_vec_tbl_el3_cur_sp0_irq:
    eret
.balign 0x80
/* FIQ */
_vec_tbl_el3_cur_sp0_fiq:
    eret
.balign 0x80
/* SError */
_vec_tbl_el3_cur_sp0_err:
    eret
.balign 0x80
_vec_tbl_el3_cur_spx:
/* Synchronous Abort */
_vec_tbl_el3_cur_spx_syn:
    eret
.balign 0x80
/* IRQ */
_vec_tbl_el3_cur_spx_irq:
    eret
.balign 0x80
/* FIQ */
_vec_tbl_el3_cur_spx_fiq:
    eret
.balign 0x80
/* SError */
_vec_tbl_el3_cur_spx_err:
    eret
.balign 0x80
_vec_tbl_el3_low_64:
/* Synchronous Abort */
_vec_tbl_el3_low_64_syn:
    eret
.balign 0x80
/* IRQ */
_vec_tbl_el3_low_64_irq:
    eret
.balign 0x80
/* FIQ */
_vec_tbl_el3_low_64_fiq:
    eret
.balign 0x80
/* SError */
_vec_tbl_el3_low_64_err:
    eret
.balign 0x80
_vec_tbl_el3_low_32:
/* Synchronous Abort */
_vec_tbl_el3_low_32_syn:
    eret
.balign 0x80
/* IRQ */
_vec_tbl_el3_low_32_irq:
    eret
.balign 0x80
/* FIQ */
_vec_tbl_el3_low_32_fiq:
    eret
.balign 0x80
/* SError */
_vec_tbl_el3_low_32_err:
    eret
.balign 0x80
_vec_tbl_el3_e:

/* TODO: Vector table EL2 */
.balign 0x800
_vec_tbl_el2_s:
_vec_tbl_el2_cur_sp0:
/* Synchronous Abort */
_vec_tbl_el2_cur_sp0_syn:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #0
    mrs x2, ESR_EL2
    mrs x3, FAR_EL2
    b _exce_handler
.balign 0x80
/* IRQ */
_vec_tbl_el2_cur_sp0_irq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #1
    b _intr_handler
.balign 0x80
/* FIQ */
_vec_tbl_el2_cur_sp0_fiq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #2
    b _intr_handler
.balign 0x80
/* SError */
_vec_tbl_el2_cur_sp0_err:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #3
    mrs x2, ESR_EL2
    mrs x3, FAR_EL2
    b _exce_handler
.balign 0x80
_vec_tbl_el2_cur_spx:
/* Synchronous Abort */
_vec_tbl_el2_cur_spx_syn:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #4
    mrs x2, ESR_EL2
    mrs x3, FAR_EL2
    b _exce_handler
.balign 0x80
/* IRQ */
_vec_tbl_el2_cur_spx_irq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #5
    b _intr_handler
.balign 0x80
_vec_tbl_el2_cur_spx_fiq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #6
    b _intr_handler
.balign 0x80
/* SError */
_vec_tbl_el2_cur_spx_err:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #7
    mrs x2, ESR_EL2
    mrs x3, FAR_EL2
    b _exce_handler
.balign 0x80
_vec_tbl_el2_low_64:
/* Synchronous Abort */
_vec_tbl_el2_low_64_syn:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #8
    mrs x2, ESR_EL2
    mrs x3, FAR_EL2
    b _exce_handler
.balign 0x80
/* IRQ */
_vec_tbl_el2_low_64_irq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #9
    b _intr_handler
.balign 0x80
/* FIQ */
_vec_tbl_el2_low_64_fiq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #10
    b _intr_handler
.balign 0x80
/* SError */
_vec_tbl_el2_low_64_err:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #11
    mrs x2, ESR_EL2
    mrs x3, FAR_EL2
    b _exce_handler
.balign 0x80
_vec_tbl_el2_low_32:
/* Synchronous Abort */
_vec_tbl_el2_low_32_syn:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #12
    mrs x2, ESR_EL2
    mrs x3, FAR_EL2
    b _exce_handler
.balign 0x80
_vec_tbl_el2_low_32_irq:
/* IRQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #13
    b _intr_handler
.balign 0x80
/* FIQ */
_vec_tbl_el2_low_32_fiq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #14
    b _intr_handler
.balign 0x80
/* SError */
_vec_tbl_el2_low_32_err:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #2
    mov x1, #15
    mrs x2, ESR_EL2
    mrs x3, FAR_EL2
    b _exce_handler
.balign 0x80
_vec_tbl_el2_e:

/* TODO: Vector table EL1 */
.balign 0x800
_vec_tbl_el1_s:
_vec_tbl_el1_cur_sp0:
/* Synchronous Abort */
_vec_tbl_el1_cur_sp0_syn:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #0
    mrs x2, ESR_EL1
    mrs x3, FAR_EL1
    b _exce_handler
.balign 0x80
/* IRQ */
_vec_tbl_el1_cur_sp0_irq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #1
    b _intr_handler
.balign 0x80
/* FIQ */
_vec_tbl_el1_cur_sp0_fiq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #2
    b _intr_handler
.balign 0x80
/* SError */
_vec_tbl_el1_cur_sp0_err:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #3
    mrs x2, ESR_EL1
    mrs x3, FAR_EL1
    b _exce_handler
.balign 0x80
_vec_tbl_el1_cur_spx:
/* Synchronous Abort */
_vec_tbl_el1_cur_spx_syn:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #4
    mrs x2, ESR_EL1
    mrs x3, FAR_EL1
    b _exce_handler
.balign 0x80
_vec_tbl_el1_cur_spx_irq:
/* IRQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #5
    b _intr_handler
.balign 0x80
/* FIQ */
_vec_tbl_el1_cur_spx_fiq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #6
    b _intr_handler
.balign 0x80
/* SError */
_vec_tbl_el1_cur_spx_err:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #7
    mrs x2, ESR_EL1
    mrs x3, FAR_EL1
    b _exce_handler
.balign 0x80
_vec_tbl_el1_low_64:
/* Synchronous Abort */
_vec_tbl_el1_low_64_syn:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #8
    mrs x2, ESR_EL1
    mrs x3, FAR_EL1
    b _exce_handler
.balign 0x80
_vec_tbl_el1_low_64_irq:
/* IRQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #9
    b _intr_handler
.balign 0x80
/* FIQ */
_vec_tbl_el1_low_64_fiq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #10
    b _intr_handler
.balign 0x80
_vec_tbl_el1_low_64_err:
/* SError */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #11
    mrs x2, ESR_EL1
    mrs x3, FAR_EL1
    b _exce_handler
.balign 0x80
_vec_tbl_el1_low_32:
/* Synchronous Abort */
_vec_tbl_el1_low_32_syn:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #12
    mrs x2, ESR_EL1
    mrs x3, FAR_EL1
    b _exce_handler
.balign 0x80
_vec_tbl_el1_low_32_irq:
/* IRQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x0, #13
    b _intr_handler
.balign 0x80
/* FIQ */
_vec_tbl_el1_low_32_fiq:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #14
    b _intr_handler
.balign 0x80
/* SError */
_vec_tbl_el1_low_32_err:
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mov x0, #1
    mov x1, #15
    mrs x2, ESR_EL1
    mrs x3, FAR_EL1
    b _exce_handler
.balign 0x80
_vec_tbl_el1_e:

/* Exception handler */
_exce_handler:
    bl exce_handler
    ldp x0, x1, [sp], #16
    ldp x2, x3, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x29, x30, [sp], #16
    eret

/* Interrupt handler */
_intr_handler:
    bl intr_handler
    ldp x0, x1, [sp], #16
    ldp x2, x3, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x29, x30, [sp], #16
    eret

.text

FUNCTION(_cpu_el3_vec_tbl_set)
    ldr x0, =_vec_tbl_el3_s
    msr VBAR_EL3, x0
    ret

FUNCTION(_cpu_el2_vec_tbl_set)
    ldr x0, =_vec_tbl_el2_s
    msr VBAR_EL2, x0
    ret

FUNCTION(_cpu_el1_vec_tbl_set)
    ldr x0, =_vec_tbl_el1_s
    msr VBAR_EL1, x0
    ret

.end
