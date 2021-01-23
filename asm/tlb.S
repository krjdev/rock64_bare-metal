/**
 *
 * File Name: asm/tlb.S
 * Title    : AArch64 Memory Translation
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-23
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

#include <asm.h>

#define TLB_4K              4096

/* Virtual Memory Address offset with 4KiB granule */
#define TLB_4K_VMA_LEVEL0   39
#define TLB_4K_VMA_LEVEL1   29
#define TLB_4K_VMA_LEVEL2   20
#define TLB_4K_VMA_LEVEL3   11

.section .pagetable ,"awx",%nobits
/* EL2 Pagetables */
.align 12
_tlb_el2_tbb0_lv0:
.space TLB_4K
.align 12
_tlb_el2_tbb0_lv1_0:
.space TLB_4K
.align 12
_tlb_el2_tbb0_lv1_0_kernel:
.space TLB_4K
.align 12
_tlb_el2_tbb0_lv1_0_mmio:
.space TLB_4K
.align 12
/* EL1 Pagetables */
_tlb_el1_tbb0_lv0:
.space TLB_4K
.align 12
_tlb_el1_tbb0_lv1_0:
.space TLB_4K
.align 12
_tlb_el1_tbb0_lv1_0_kernel:
.space TLB_4K
.align 12
_tlb_el1_tbb0_lv1_0_mmio:
.space TLB_4K

.text

FUNCTION(_cpu_el2_tlb_create)
    /* Zero Level 0 table */
    ldr x0, =_tlb_el2_tbb0_lv0
    mov x1, #512
__el2_tbb0_lv0_zero:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp xzr, x1
    bne __el2_tbb0_lv0_zero
    /* */
__el2_tbb0_lv0:
    ldr x0, =_tlb_el2_tbb0_lv0
    ldr x1, =_tlb_el2_tbb0_lv1_0
    orr x1, x1, #0x3
    str x1, [x0], #0
    /* Zero Level 1 index 0 table */
    ldr x0, =_tlb_el2_tbb0_lv1_0
    mov x1, #512
__el2_tbb0_lv1_0_zero:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp xzr, x1
    bne __el2_tbb0_lv1_0_zero
__el2_tbb0_lv1_0_kernel:
    ldr x0, =_tlb_el2_tbb0_lv1_0
    ldr x1, =_tlb_el2_tbb0_lv1_0_kernel
    orr x1, x1, #0x3
    str x1, [x0, #16]
    ldr x0, =_tlb_el2_tbb0_lv1_0_kernel
    mov x1, #512
__el2_tbb0_lv1_0_kernel_zero:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp xzr, x1
    bne __el2_tbb0_lv1_0_kernel_zero
    /* Kernel 512MiB@0x80000000 */
    ldr x0, =_tlb_el2_tbb0_lv1_0_kernel
    ldr x3, =0x80000000
    ldr x2, =0x200000
    mov x1, #256
__el2_tbb0_lv1_0_kernel_block:
    mov x4, 0x711
    orr x5, x3, x4
    str x5, [x0], #8
    add x3, x3, x2
    subs x1, x1, #1
    cmp xzr, x1
    bne __el2_tbb0_lv1_0_kernel_block
__el2_tbb0_lv1_0_mmio:
    ldr x0, =_tlb_el2_tbb0_lv1_0
    ldr x1, =_tlb_el2_tbb0_lv1_0_mmio
    orr x1, x1, #0x3
    str x1, [x0, #24]
    ldr x0, =_tlb_el2_tbb0_lv1_0_mmio
    mov x1, #512
__el2_tbb0_lv1_0_mmio_zero:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp xzr, x1
    bne __el2_tbb0_lv1_0_mmio_zero
    /* MMIO 16MiB@0xFF000000 */
    ldr x0, =_tlb_el2_tbb0_lv1_0_mmio
    ldr x3, =0xC0000000
    ldr x6, =0xFF000000
    ldr x2, =0x200000
    mov x1, #512
__el2_tbb0_lv1_0_mmio_skip:
    add x3, x3, x2
    subs x1, x1, #1
    add x0, x0, #8
    cmp x3, x6
    bne __el2_tbb0_lv1_0_mmio_skip
__el2_tbb0_lv1_0_mmio_block:
    mov x4, 0x401
    orr x5, x3, x4
    str x5, [x0], #8
    add x3, x3, x2
    subs x1, x1, #1
    cmp xzr, x1
    bne __el2_tbb0_lv1_0_mmio_block
__el2_tbb0_setup:
    ldr x0, =0x80803517
    msr TCR_EL2, x0
    ldr x0, =0xFF440C0400
    msr MAIR_EL2, x0
    ldr x0, =_tlb_el2_tbb0_lv0
    msr TTBR0_EL2, x0
    dsb sy
    ret

FUNCTION(_cpu_el1_tlb_create)
    /* Zero Level 0 table */
    ldr x0, =_tlb_el1_tbb0_lv0
    mov x1, #512
__el1_tbb0_lv0_zero:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp xzr, x1
    bne __el1_tbb0_lv0_zero
    /* */
__el1_tbb0_lv0:
    ldr x0, =_tlb_el1_tbb0_lv0
    ldr x1, =_tlb_el1_tbb0_lv1_0
    orr x1, x1, #0x3
    str x1, [x0], #0
    /* Zero Level 1 index 0 table */
    ldr x0, =_tlb_el1_tbb0_lv1_0
    mov x1, #512
__el1_tbb0_lv1_0_zero:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp xzr, x1
    bne __el1_tbb0_lv1_0_zero
__el1_tbb0_lv1_0_kernel:
    ldr x0, =_tlb_el1_tbb0_lv1_0
    ldr x1, =_tlb_el1_tbb0_lv1_0_kernel
    orr x1, x1, #0x3
    str x1, [x0, #16]
    ldr x0, =_tlb_el1_tbb0_lv1_0_kernel
    mov x1, #512
__el1_tbb0_lv1_0_kernel_zero:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp xzr, x1
    bne __el1_tbb0_lv1_0_kernel_zero
    /* Kernel 512MiB@0x80000000 */
    ldr x0, =_tlb_el1_tbb0_lv1_0_kernel
    ldr x3, =0x80000000
    ldr x2, =0x200000
    mov x1, #256
__el1_tbb0_lv1_0_kernel_block:
    mov x4, 0x711
    orr x5, x3, x4
    str x5, [x0], #8
    add x3, x3, x2
    subs x1, x1, #1
    cmp xzr, x1
    bne __el1_tbb0_lv1_0_kernel_block
__el1_tbb0_lv1_0_mmio:
    ldr x0, =_tlb_el1_tbb0_lv1_0
    ldr x1, =_tlb_el1_tbb0_lv1_0_mmio
    orr x1, x1, #0x3
    str x1, [x0, #24]
    ldr x0, =_tlb_el1_tbb0_lv1_0_mmio
    mov x1, #512
__el1_tbb0_lv1_0_mmio_zero:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp xzr, x1
    bne __el1_tbb0_lv1_0_mmio_zero
    /* MMIO 16MiB@0xFF000000 */
    ldr x0, =_tlb_el1_tbb0_lv1_0_mmio
    ldr x3, =0xC0000000
    ldr x6, =0xFF000000
    ldr x2, =0x200000
    mov x1, #512
__el1_tbb0_lv1_0_mmio_skip:
    add x3, x3, x2
    subs x1, x1, #1
    add x0, x0, #8
    cmp x3, x6
    bne __el1_tbb0_lv1_0_mmio_skip
__el1_tbb0_lv1_0_mmio_block:
    mov x4, 0x401
    orr x5, x3, x4
    str x5, [x0], #8
    add x3, x3, x2
    subs x1, x1, #1
    cmp xzr, x1
    bne __el1_tbb0_lv1_0_mmio_block
__el1_tbb0_setup:
    ldr x0, =0x803517
    msr TCR_EL1, x0
    ldr x0, =0xFF440C0400
    msr MAIR_EL1, x0
    ldr x0, =_tlb_el1_tbb0_lv0
    msr TTBR0_EL1, x0
    dsb sy
    ret

FUNCTION(_cpu_el2_tlb_tcr)
    mrs x0, TCR_EL2
    ret

FUNCTION(_cpu_el2_tlb_mair)
    mrs x0, MAIR_EL2
    ret

FUNCTION(_cpu_el2_tlb_tbbr0)
    mrs x0, TTBR0_EL2
    ret

FUNCTION(_cpu_el1_tlb_tcr)
    mrs x0, TCR_EL1
    ret

FUNCTION(_cpu_el1_tlb_mair)
    mrs x0, MAIR_EL1
    ret

FUNCTION(_cpu_el1_tlb_tbbr0)
    mrs x0, TTBR0_EL1
    ret

.end
