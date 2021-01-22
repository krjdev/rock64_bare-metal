/**
 *
 * File Name: asm/cache.S
 * Title    : Cortex-A53 Cache Maintenance Functions
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-21
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

.text

/* Clean and invalidate I-Cache */
FUNCTION(_cpu_icache_invalidate)
    ic IALLUIS
    dsb sy
    isb
    ret

/* Clean and invalidate Level 1 D-Cache */
FUNCTION(_cpu_dcache_l1_invalidate)
    mov x0, xzr
    msr CSSELR_EL1, x0
    mrs x4, CCSIDR_EL1
    and x1, x4, #0x7
    add x1, x1, #0x4
    ldr x3, =0x7FFF
    and x2, x3, x4, lsr #13
    ldr x3, =0x3FF
    and x3, x3, x4, lsr #3
    clz w4, w3
    mov x5, #0
__d_l1_way:
    mov x6, #0
__d_l1_set:
    lsl x7, x5, x4
    orr x7, x0, x7
    lsl x8, x6, x1
    orr x7, x7, x8
    dc CISW, x7
    add x6, x6, #1
    cmp x6, x2
    ble __d_l1_set
    add x5, x5, #1
    cmp x5, x3
    ble __d_l1_way
    dsb sy
    isb
    mov x8, xzr
    ret

/* Clean and invalidate Level 2 D-Cache */
FUNCTION(_cpu_dcache_l2_invalidate)
    mov x0, xzr
    orr x0, x0, #(1 << 1)
    msr CSSELR_EL1, x0
    mrs x4, CCSIDR_EL1
    and x1, x4, #0x7
    add x1, x1, #0x4
    ldr x3, =0x7FFF
    and x2, x3, x4, lsr #13
    ldr x3, =0x3FF
    and x3, x3, x4, lsr #3
    clz w4, w3
    mov x5, #0
__d_l2_way:
    mov x6, #0
__d_l2_set:
    lsl x7, x5, x4
    orr x7, x0, x7
    lsl x8, x6, x1
    orr x7, x7, x8
    dc CISW, x7
    add x6, x6, #1
    cmp x6, x2
    ble __d_l2_set
    add x5, x5, #1
    cmp x5, x3
    ble __d_l2_way
    dsb sy
    isb
    mov x8, xzr
    ret

.end
