/**
 *
 * File Name: include/kern/asm/self.h
 * Title    : Kernel Library
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

#ifndef ROCK64_KERN_ASM_SELF_H
#define ROCK64_KERN_ASM_SELF_H

#include <stdint.h>

extern uint64_t _self_get_heap_s(void);
extern uint64_t _self_get_heap_e(void);

#endif
