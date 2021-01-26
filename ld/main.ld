/**
 *
 * File Name: ld/main.ld
 * Title    : Global Linker Script
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

ENTRY(_start_kern)

MEMORY {
    RAM_KERN (rwx) : ORIGIN = 0x80000000, LENGTH = 512M
    RAM_USER (rwx) : ORIGIN = 0x40000000, LENGTH = 1024M
}

SECTIONS {
    .kern_text :  {
        kern.elf (.text)
     } > RAM_KERN
    
    .kern_rodata :  {
        kern.elf (.rodata)
     } > RAM_KERN
    
    .kern_data :  {
        kern.elf (.data)
     } > RAM_KERN
    
    .kern_bss (NOLOAD) :  {
        kern.elf (.bss)
     } > RAM_KERN
    
    .kern_data (NOLOAD) :  {
        kern.elf (.data)
     } > RAM_KERN
    
    .kern_tlb (NOLOAD) :  {
        kern.elf (.tlb)
     } > RAM_KERN
    
    .kern_heap (NOLOAD) :  {
        kern.elf (.heap)
     } > RAM_KERN
    
    .kern_stack (NOLOAD) :  {
        kern.elf (.stack)
     } > RAM_KERN
    
    .user_text :  {
        user.elf (.text)
     } > RAM_USER
    
    .user_rodata :  {
        user.elf (.rodata)
     } > RAM_USER
    
    .user_data :  {
        user.elf (.data)
     } > RAM_USER
    
    .user_bss (NOLOAD) :  {
        user.elf (.bss)
     } > RAM_USER
}
