/**
 *
 * File Name: asm/start.S
 * Title    : AArch64 Main Entry Point
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

IMPORT_ASM(_cpu_el3_vec_tbl_set)
IMPORT_ASM(_cpu_el2_vec_tbl_set)
IMPORT_ASM(_cpu_el1_vec_tbl_set)

IMPORT_ASM(_cpu_icache_invalidate)
IMPORT_ASM(_cpu_dcache_l1_invalidate)
IMPORT_ASM(_cpu_dcache_l2_invalidate)

IMPORT_ASM(_cpu_el2_tlb_create)
IMPORT_ASM(_cpu_el1_tlb_create)

IMPORT_C(init)
IMPORT_C(main)

#define CONFIG_MMU_EL2
#define CONFIG_MMU_EL1

.text

ENTRY(_start)
#ifndef CONFIG_SMP
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #0
    bne __cpux_wfe
#endif
__elx_enter:
__el3_enter:
    mrs x0, CurrentEL
    and x0, x0, #0xC
    asr x0, x0, #2
    cmp x0, #3
    bne __el2_enter
__el3_stack_cpu0:
#ifdef CONFIG_SMP
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #0
    bne __el3_stack_cpu1
#endif
    ldr x0, =_stack_cpu0_el3_e
    mov sp, x0
#ifdef CONFIG_SMP
    b __el3_vector
__el3_stack_cpu1:
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #1
    bne __el3_stack_cpu2
    ldr x0, =_stack_cpu1_el3_e
    mov sp, x0
    b __el3_vector
__el3_stack_cpu2:
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #2
    bne __el3_stack_cpu3
    ldr x0, =_stack_cpu2_el3_e
    mov sp, x0
    b __el3_vector
__el3_stack_cpu3:
    ldr x0, =_stack_cpu3_el3_e
    mov sp, x0
#endif
__el3_vector:
    bl _cpu_el3_vec_tbl_set
    msr DAIFclr, #7
__el3_setup_el2:
    msr SCTLR_EL2, xzr
    msr HCR_EL2, xzr
    mrs x0, SCR_EL3
    orr x0, x0, #(1 << 10) /* Next lower exception level is AArch64 */
    orr x0, x0, #(1 << 0)  /* EL1/El0 are in Non-secure state */
    msr SCR_EL3, x0
__el3_exit:
    mov x0, xzr
    orr x0, x0, #(1 << 8)  /* Mask SError */
    orr x0, x0, #(1 << 7)  /* Mask IRQ */
    orr x0, x0, #(1 << 6)  /* Mask FIQ */
    mov x1, #0b01001       /* EL2 is in handler mode */
    orr x0, x0, x1
    msr SPSR_EL3, x0
    adr x0, __el2_enter
    msr ELR_EL3, x0
    eret
    
__el2_enter:
    msr	SPsel, #1 
    mrs x0, CurrentEL
    and x0, x0, #0xC
    asr x0, x0, #2
    cmp x0, #2
    bne __el1_enter
__el2_stack_cpu0:
#ifdef CONFIG_SMP
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #0
    bne __el2_stack_cpu1
#endif
    ldr x0, =_stack_cpu0_el2_e
    mov sp, x0
#ifdef CONFIG_SMP
    b __el3_vector
__el2_stack_cpu1:
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #1
    bne __el3_stack_cpu2
    ldr x0, =_stack_cpu1_el2_e
    mov sp, x0
    b __el3_vector
__el2_stack_cpu2:
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #2
    bne __el3_stack_cpu3
    ldr x0, =_stack_cpu2_el2_e
    mov sp, x0
    b __el3_vector
__el2_stack_cpu3:
    ldr x0, =_stack_cpu3_el2_e
    mov sp, x0
#endif
__el2_vector:
    bl _cpu_el2_vec_tbl_set
    msr DAIFclr, #7
#ifdef CONFIG_MMU_EL2
__el2_cache:
    mrs x0, SCTLR_EL2
    bic x0, x0, #(1 << 0)  /* Disable MMU */
    bic x0, x0, #(1 << 2)  /* Disable D-Cache */
    bic x0, x0, #(1 << 12) /* Disable I-Cache */
    msr SCTLR_EL2, x0
    isb

    /* Invalidate and clean I/D-Cache */
    bl _cpu_icache_invalidate
    bl _cpu_dcache_l1_invalidate
    bl _cpu_dcache_l2_invalidate
    
__el2_pagetable:
    /* Create pagetable for EL2 */
    bl _cpu_el2_tlb_create
    
    /* Invalidate (old) Pagetable */
    tlbi ALLE2
    dsb sy
    isb
    
    mrs x0, SCTLR_EL2
    orr x0, x0, #(1 << 0)  /* Enable MMU */
    orr x0, x0, #(1 << 2)  /* Enable D-Cache */
    orr x0, x0, #(1 << 12) /* Enable I-Cache */
    msr SCTLR_EL2, x0 
    isb
    nop
    nop
    nop
    nop
#endif
__el2_setup_el1:
    mrs x0, HCR_EL2
    orr x0, x0, #(1 << 31) /* EL1 is AArch64 */
    msr HCR_EL2, x0
    /* Setup Stack for EL1 */
    ldr x0, =_stack_cpu0_el1_e
    msr SP_EL1, x0
    /* Setup Stack for EL0 */
    ldr x0, =_stack_cpu0_el0_e
    msr SP_EL0, x0
    
    mov x0, xzr
    orr x0, x0, #(1 << 29) /* RES1 */
    orr x0, x0, #(1 << 28) /* RES1 */
    orr x0, x0, #(1 << 23) /* RES1 */
    orr x0, x0, #(1 << 22) /* RES1 */
    orr x0, x0, #(1 << 20) /* RES1 */
    orr x0, x0, #(1 << 11) /* RES1 */
    orr x0, x0, #(1 << 4)  /* Enable SP aligment check for EL0 */
    orr x0, x0, #(1 << 3)  /* Enable SP aligment check for EL1 */
    orr x0, x0, #(1 << 1)  /* Enable aligment fault check */
    msr SCTLR_EL1, x0
    
__el2_timer:
    /* Enable Timer for EL1 */
    mrs x0, CNTHCTL_EL2
    orr x0, x0, #(1 << 0)
    orr x0, x0, #(1 << 1)
    msr CNTHCTL_EL2, x0
    msr CNTVOFF_EL2, xzr
    
__el2_exit:
    mov x0, xzr
    orr x0, x0, #(1 << 8) /* Mask SError */
    orr x0, x0, #(1 << 7) /* Mask IRQ */
    orr x0, x0, #(1 << 6) /* Mask FIQ */
    bic x0, x0, #(1 << 4) /* AArch64 execution state */
    mov x1, #0b101        /* EL1 is in handler mode */
    orr x0, x0, x1
    msr SPSR_EL2, x0
    adr x0, __el1_enter
    msr ELR_EL2, x0
    eret
    
__el1_enter:
__el1_stack_cpu0:
#ifdef CONFIG_SMP
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #0
    bne __el1_stack_cpu1
#endif
    msr SPsel, #1
    ldr x0, =_stack_cpu0_el1_e
    mov sp, x0
    msr SPsel, #0
    ldr x0, =_stack_cpu0_el0_e
    mov sp, x0
    msr SPsel, #1
#ifdef CONFIG_SMP
    b __el1_vector
__el1_stack_cpu1:
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #1
    bne __el3_stack_cpu2
    msr SPsel, #1
    ldr x0, =_stack_cpu1_el1_e
    mov sp, x0
    msr SPsel, #0
    ldr x0, =_stack_cpu1_el0_e
    mov sp, x0
    msr SPsel, #1
    b __el1_vector
__el1_stack_cpu2:
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #2
    bne __el3_stack_cpu3
    msr SPsel, #1
    ldr x0, =_stack_cpu2_el1_e
    mov sp, x0
    msr SPsel, #0
    ldr x0, =_stack_cpu2_el0_e
    mov sp, x0
    msr SPsel, #1
    b __el1_vector
__el1_stack_cpu3:
    msr SPsel, #1
    ldr x0, =_stack_cpu3_el1_e
    mov sp, x0
    msr SPsel, #0
    ldr x0, =_stack_cpu3_el0_e
    mov sp, x0
    msr SPsel, #1
#endif
__el1_vector:
    bl _cpu_el1_vec_tbl_set
    msr DAIFclr, #7
#ifdef CONFIG_MMU_EL1
__el1_cache:
    mrs x0, SCTLR_EL1
    bic x0, x0, #(1 << 0)  /* Disable MMU */
    bic x0, x0, #(1 << 2)  /* Disable D-Cache */
    bic x0, x0, #(1 << 12) /* Disable I-Cache */
    msr SCTLR_EL1, x0
    isb

    /* Invalidate and clean I/D-Cache */
    bl _cpu_icache_invalidate
    bl _cpu_dcache_l1_invalidate
    bl _cpu_dcache_l2_invalidate
    
__el1_pagetable:
    /* Create pagetable for EL2 */
    bl _cpu_el1_tlb_create
    
    /* Invalidate (old) Pagetable */
    tlbi VMALLE1
    dsb sy
    isb
    
    mrs x0, SCTLR_EL1
    orr x0, x0, #(1 << 0)  /* Enable MMU */
    orr x0, x0, #(1 << 2)  /* Enable D-Cache */
    orr x0, x0, #(1 << 12) /* Enable I-Cache */
    msr SCTLR_EL1, x0 
    isb
    nop
    nop
    nop
    nop
#endif
#ifdef CONFIG_SMP
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cmp x0, #0
    bne __cpux_wfe
#endif
    /* Zero BSS */
__el1_bss:
    ldr x0, =_bss_s
    ldr x1, =_bss_e
    sub x1, x1, x0
    mov x2, #0x0
    cbz x1, __el1_init
__el1_bss_loop:
    strb w2, [x0], #1
    sub x1, x1, #1
    cbnz x1, __el1_bss_loop
__el1_init:
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    bl init
__el1_main:
    bl main
    ldp x29, x30, [sp], #16
__el1_main_wfe:
    wfe
    b __el1_main_wfe

__cpux_wfe:
    wfe
    b __cpux_wfe

.end
