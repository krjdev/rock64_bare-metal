/**
 *
 * File Name: include/user/asm/asm.h
 * Title    : Simple Standard C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-25
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

#ifndef ROCK64_USER_ASM_ASM_H
#define ROCK64_USER_ASM_ASM_H

/* Import Assembler Functions */
#define IMPORT_ASM(name) \
            .extern name ;

/* Import C Functions */
#define IMPORT_C(name) \
            .extern name ;

#define _EXPORT_SYMBOL_ASM(name) \
        .globl name ; \
        name:

/* Entry (Never returns) */
#define ENTRY(name) \
        _EXPORT_SYMBOL_ASM(name)
        
/* Assembler Function */
#define FUNCTION(name) \
        _EXPORT_SYMBOL_ASM(name)

/* Assembler Function */
#define SYSCALL(name) \
        _EXPORT_SYMBOL_ASM(name)


#endif
