/**
 *
 * File Name: asm.h
 * Title    : Assembler Macros
 * Project  : 
 * Author   : Copyright (C) 2020 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2020-06-05
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

#ifndef ASM_H
#define ASM_H

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

/* Interrupt Service Routine */
#define ISR(name) \
        _EXPORT_SYMBOL_ASM(name)

#endif
