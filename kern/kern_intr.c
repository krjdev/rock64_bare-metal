/**
 *
 * File Name: kern/kern_intr.c
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

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <kern/panic.h>

#define EXCP_LEVEL_EL1      1
#define EXCP_LEVEL_EL2      2

#define INTR_INDEX_FIQ      1
#define INTR_INDEX_IRQ      2

#define INTR_MAX            64

#define INTR_FLAG_USED      0x00000001

struct _kern_intr {
    uint32_t flags;
    int irq_nr;
    void (*handler)(void);
};

static struct _kern_intr *kern_intr_list;
static int kern_intr_size;
static int kern_intr_count;

void excp_handler(int excp_level, int index, uint64_t reg_esr, uint64_t reg_far)
{
    uint32_t ec;
    uint32_t iss;
    int il;
    
    if (excp_level == EXCP_LEVEL_EL1)
        puts("Caught exception in EL1\r\n");
    else
        puts("Caught exception in EL2\r\n");
    
    ec = (uint32_t) ((reg_esr & 0xFC000000) >> 26);
    il = (int) ((reg_esr & 0x2000000) >> 25);
    iss = (uint32_t) (reg_esr & 0x1FFFFFF);
    
    if (ec == 0x15) {
        puts("SVC: ");
        
        switch (iss) {
        case 0:
            puts("sys_exit\r\n");
            abort();
            break;
        case 1:
            puts("sys_open\r\n");
            break;
        case 2:
            puts("sys_close\r\n");
            break;
        case 3:
            puts("sys_write\r\n");
            break;
        case 4:
            puts("sys_read\r\n");
            break;
        case 5:
            puts("sys_sleep\r\n");
            break;
        case 6:
            puts("sys_abort\r\n");
            abort();
            break;
        default:
            puts("sys_unknown\r\n");
        }
    } else {
        puts("Caught unkown exception\r\n");
        kern_panic(__func__, 0);
    }
}

void intr_handler(int excp_level, int index)
{
    int i;
    struct _kern_intr *intr;
    
    if (excp_level == EXCP_LEVEL_EL2) {
        puts("Caught interrupt from EL2\r\n");
        kern_panic(__func__, 0);
    }
    
    if (index == INTR_INDEX_FIQ) {
        puts("Caught FIQ\r\n");
        kern_panic(__func__, 0);
    } else {
        puts("Caught IRQ\r\n");
        kern_panic(__func__, 0);
    }
    
    for (i = 0; i < kern_intr_size; i++) {
        intr = &kern_intr_list[i];
        
        if (!(intr->flags & INTR_FLAG_USED))
            continue;
    }
}

void kern_excp_register(int type, void (*handler)(void))
{
    
}

int kern_intr_register(int irq_nr, void (*handler)(void))
{
    
}

int kern_intr_init(void)
{
    struct _kern_intr *intr;
    
    kern_intr_list = NULL;
    intr = (struct _kern_intr *) malloc(sizeof(struct _kern_intr) * INTR_MAX);
    
    if (!intr)
        return ENOMEM;
    
    kern_intr_list = intr;
    memset(kern_intr_list, 0, sizeof(struct _kern_intr) * INTR_MAX);
    kern_intr_size = INTR_MAX;
    kern_intr_count = 0;
    return ESUCCESS;
}
