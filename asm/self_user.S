/**
 *
 * File Name: asm/self_user.S
 * Title    : AArch64 Self
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-25
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
FUNCTION(_self_user_get_s)
    ldr x0, =_user_s
    ret

/* All sections end */
FUNCTION(_self_user_get_e)
    ldr x0, =_user_e
    ret

/* Section .text start */
FUNCTION(_self_user_get_text_s)
    ldr x0, =_user_text_s
    ret

/* Section .text end */
FUNCTION(_self_user_get_text_e)
    ldr x0, =_user_text_e
    ret

/* Section .rodata start */
FUNCTION(_self_user_get_rodata_s)
    ldr x0, =_user_rodata_s
    ret

/* Section .rodata end */
FUNCTION(_self_user_get_rodata_e)
    ldr x0, =_user_rodata_e
    ret

/* Section .data start */
FUNCTION(_self_user_get_data_s)
    ldr x0, =_user_data_s
    ret

/* Section .data end */
FUNCTION(_self_user_get_data_e)
    ldr x0, =_user_data_e
    ret

/* Section .bss start */
FUNCTION(_self_user_get_bss_s)
    ldr x0, =_user_bss_s
    ret

/* Section .bss end */
FUNCTION(_self_user_get_bss_e)
    ldr x0, =_user_bss_e
    ret
/* Section .heap start */
FUNCTION(_self_user_get_heap_s)
    ldr x0, =_user_heap_s
    ret

/* Section .heap start */
FUNCTION(_self_user_get_heap_e)
    ldr x0, =_user_heap_e
    ret

.end
