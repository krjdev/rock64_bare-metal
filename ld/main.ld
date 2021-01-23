/**
 *
 * File Name: ld/main.ld
 * Title    : Linker Script
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

ENTRY(_start)

MEMORY {
    RAM_KERN (rwx) : ORIGIN = 0x80000000, LENGTH = 512M
}

STACK_EL3 = 4K;
STACK_EL2 = 4K;
STACK_EL1 = 64M;
STACK_EL0 = 1M;

SECTIONS {
    _s = .;
    
    .text :  {
        _text_s = .;
        KEEP(*(.isr_vector))
        *(.text)
        *(.text*)
        _text_e = .;
        
    } > RAM_KERN
    
    .rodata : {
        . = ALIGN(4K);
        _rodata_s = .;
        *(.rodata)
        *(.rodata*)
        _rodata_e = .;
    } > RAM_KERN
    
    .data :  {
        . = ALIGN(4K);
        _data_s = .;
        *(.data)
        *(.data*)
        _data_e = .;
    } > RAM_KERN
    
    .bss (NOLOAD):  {
        . = ALIGN(4K);
        _bss_s = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        _bss_e = .;
    } > RAM_KERN
    
    .tlb (NOLOAD): {
        . = ALIGN(16K);
        _tlb_s = .;
        KEEP(*(.pagetable))
        _tlb_e = .;
    } > RAM_KERN
    
    STACK = (4 * STACK_EL3) + (4 * STACK_EL2) + (4 * STACK_EL1) + (4 * STACK_EL0);
    HEAP_SIZE = (ORIGIN(RAM_KERN) + LENGTH(RAM_KERN)) - _heap_s - STACK;
        
    .heap (NOLOAD): {
        . = ALIGN(4);
        _heap_s = .;
        . = . + HEAP_SIZE;
        _heap_e = .;
    } > RAM_KERN
    
    .stack (NOLOAD):  {
        /* EL0 */
        . = ALIGN(4K);
        _stack_el0_s = .;
        _stack_cpu0_el0_s = .;
        . = . + STACK_EL0;
        _stack_cpu0_el0_e = .;
        . = ALIGN(4K);
        _stack_cpu1_el0_s = .;
        . = . + STACK_EL0;
        _stack_cpu1_el0_e = .;
        . = ALIGN(4K);
        _stack_cpu2_el0_s = .;
        . = . + STACK_EL0;
        _stack_cpu2_el0_e = .;
        . = ALIGN(4K);
        _stack_cpu3_el0_s = .;
        . = . + STACK_EL0;
        _stack_cpu3_el0_e = .;
        _stack_el0_e = .;
        
        /* EL1 */
        . = ALIGN(4K);
        _stack_el1_s = .;
        _stack_cpu0_el1_s = .;
        . = . + STACK_EL1;
        _stack_cpu0_el1_e = .;
        . = ALIGN(4K);
        _stack_cpu1_el1_s = .;
        . = . + STACK_EL1;
        _stack_cpu1_el1_e = .;
        . = ALIGN(4K);
        _stack_cpu2_el1_s = .;
        . = . + STACK_EL1;
        _stack_cpu2_el1_e = .;
        . = ALIGN(4K);
        _stack_cpu3_el1_s = .;
        . = . + STACK_EL1;
        _stack_cpu3_el1_e = .;
        _stack_el1_e = .;
        
        /* EL2 */
        . = ALIGN(4K);
        _stack_el2_s = .;
        _stack_cpu0_el2_s = .;
        . = . + STACK_EL2;
        _stack_cpu0_el2_e = .;
        . = ALIGN(4K);
        _stack_cpu1_el2_s = .;
        . = . + STACK_EL2;
        _stack_cpu1_el2_e = .;
        . = ALIGN(4K);
        _stack_cpu2_el2_s = .;
        . = . + STACK_EL2;
        _stack_cpu2_el2_e = .;
        . = ALIGN(4K);
        _stack_cpu3_el2_s = .;
        . = . + STACK_EL2;
        _stack_cpu3_el2_e = .;
        _stack_el2_e = .;
        
        /* EL3 */
        . = ALIGN(4K);
        _stack_el3_s = .;
        _stack_cpu0_el3_s = .;
        . = . + STACK_EL3;
        _stack_cpu0_el3_e = .;
        . = ALIGN(4K);
        _stack_cpu1_el3_s = .;
        . = . + STACK_EL3;
        _stack_cpu1_el3_e = .;
        . = ALIGN(4K);
        _stack_cpu2_el3_s = .;
        . = . + STACK_EL3;
        _stack_cpu2_el3_e = .;
        . = ALIGN(4K);
        _stack_cpu3_el3_s = .;
        . = . + STACK_EL3;
        _stack_cpu3_el3_e = .;
        _stack_el3_e = .;
    } > RAM_KERN
    
    _e = .;
}
