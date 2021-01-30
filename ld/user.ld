/**
 *
 * File Name: ld/user.ld
 * Title    : Linker Script for User Application
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-25
 * Modified : 2021-01-30
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : ISC (see LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

ENTRY(_start)

MEMORY {
    RAM_USER (rwx) : ORIGIN = 0x40000000, LENGTH = 1024M
}

/* Inital User Heap size */
USER_HEAP_SIZE = 4K;

SECTIONS {
    _user_s = .;
    
    .text :  {
        . = ALIGN(4K);
        _user_text_s = .;
        *(.text)
        *(.text*)
        _user_text_e = .;
        
    } > RAM_USER
    
    .rodata : {
        . = ALIGN(4K);
        _user_rodata_s = .;
        *(.rodata)
        *(.rodata*)
        _user_rodata_e = .;
    } > RAM_USER
    
    .data :  {
        . = ALIGN(4K);
        _user_data_s = .;
        *(.data)
        *(.data*)
        _user_data_e = .;
    } > RAM_USER
    
    .bss (NOLOAD):  {
        . = ALIGN(4K);
        _user_bss_s = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        _user_bss_e = .;
    } > RAM_USER
    
    .heap (NOLOAD): {
        . = ALIGN(4K);
        _user_heap_s = .;
        . = . + USER_HEAP_SIZE;
        _user_heap_e = .;
    } > RAM_USER
    
    _user_e = .;
}
