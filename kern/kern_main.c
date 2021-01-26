/**
 *
 * File Name: kern/kern_main.c
 * Title    : Kernel
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

#include <errno.h>
#include <stdio.h>

#include <kern/dev.h>
#include <kern/sched.h>
#include <kern/vm.h>
#include <kern/vfs.h>
#include <kern/syscall.h>
#include <kern/thread.h>
#include <kern/panic.h>
#include <kern/intr.h>

void kern_main(void)
{
    int ret;
    
    /* Setup interrupts */
    ret = kern_intr_init();
    
    if (ret != ESUCCESS)
        kern_panic(__func__, ret);
    
    /* TODO: Setup pagetables */
    ret = kern_vm_init();
    
    if (ret != ESUCCESS)
        kern_panic(__func__, ret);
    
    /* Setup devices */
    ret = kern_dev_init();
    
    if (ret != ESUCCESS)
        kern_panic(__func__, ret);
    
    /* Setup virtual filesystem */
    ret = kern_vfs_init();
    
    if (ret != ESUCCESS)
        kern_panic(__func__, ret);
    
    /* TODO: Setup syscalls */
    ret = kern_syscall_init();
    
    if (ret != ESUCCESS)
        kern_panic(__func__, ret);
    
    /* TODO: Setup scheduler */
    ret = kern_sched_init();
    
    if (ret != ESUCCESS)
        kern_panic(__func__, ret);
    
    /* TODO: Setup kernel threads */
    ret = kern_thread_init();
    
    if (ret != ESUCCESS)
        kern_panic(__func__, ret);
    
    puts("PINE64 ROCK64 Bare-Metal\r\n");
    puts("Starting user application...\r\n");
}
