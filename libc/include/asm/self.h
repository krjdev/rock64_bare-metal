/**
 *
 * File Name: libc/include/asm/self.h
 * Title    : C Library - Internal
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

#ifndef ROCK64_LIBC_ASM_SELF_H
#define ROCK64_LIBC_ASM_SELF_H

#include <stdint.h>

extern uint64_t asm_self_user_get_heap_s(void);
extern uint64_t asm_self_user_get_heap_e(void);

#endif
