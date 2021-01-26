/**
 *
 * File Name: asm/self_kern.S
 * Title    : AArch64 Self
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

#include <asm/asm.h>

/* All sections start */
FUNCTION(_self_get_s)
    ldr x0, =_s
    ret

/* All sections end */
FUNCTION(_self_get_e)
    ldr x0, =_e
    ret

/* Section .text start */
FUNCTION(_self_get_text_s)
    ldr x0, =_text_s
    ret

/* Section .text end */
FUNCTION(_self_get_text_e)
    ldr x0, =_text_e
    ret

/* Section .rodata start */
FUNCTION(_self_get_rodata_s)
    ldr x0, =_rodata_s
    ret

/* Section .rodata end */
FUNCTION(_self_get_rodata_e)
    ldr x0, =_rodata_e
    ret

/* Section .data start */
FUNCTION(_self_get_data_s)
    ldr x0, =_data_s
    ret

/* Section .data end */
FUNCTION(_self_get_data_e)
    ldr x0, =_data_e
    ret

/* Section .bss start */
FUNCTION(_self_get_bss_s)
    ldr x0, =_bss_s
    ret

/* Section .bss end */
FUNCTION(_self_get_bss_e)
    ldr x0, =_bss_e
    ret

/* Section .tlb (pagetable) start */
FUNCTION(_self_get_tlb_s)
    ldr x0, =_tlb_s
    ret

/* Section .tlb (pagetable) end */
FUNCTION(_self_get_tlb_e)
    ldr x0, =_tlb_e
    ret

/* Section .heap start */
FUNCTION(_self_get_heap_s)
    ldr x0, =_heap_s
    ret

/* Section .heap end */
FUNCTION(_self_get_heap_e)
    ldr x0, =_heap_e
    ret

/* Section .stack EL0 start */
FUNCTION(_self_get_stack_el0_s)
    ldr x0, =_stack_el0_s
    ret

/* Section .stack EL0 end */
FUNCTION(_self_get_stack_el0_e)
    ldr x0, =_stack_el0_e
    ret

/* Section .stack EL1 start */
FUNCTION(_self_get_stack_el1_s)
    ldr x0, =_stack_el1_s
    ret

/* Section .stack EL1 end */
FUNCTION(_self_get_stack_el1_e)
    ldr x0, =_stack_el1_e
    ret

/* Section .stack EL2 start */
FUNCTION(_self_get_stack_el2_s)
    ldr x0, =_stack_el2_s
    ret

/* Section .stack EL2 end */
FUNCTION(_self_get_stack_el2_e)
    ldr x0, =_stack_el2_e
    ret

/* Section .stack EL3 start */
FUNCTION(_self_get_stack_el3_s)
    ldr x0, =_stack_el3_s
    ret

/* Section .stack EL3 end */
FUNCTION(_self_get_stack_el3_e)
    ldr x0, =_stack_el3_e
    ret

.end
