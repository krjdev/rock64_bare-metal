/**
 *
 * File Name: dev/misc/clock.c
 * Title    : Generic clock controller
 * Project  : PINE64 ROCK64 Bare-Metal Example
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-28
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

#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <compiler.h>

#include <kern/dev.h>

#include <dev/uart/ioctl.h>

int clock_attach(UNUSED dev_t *self)
{
    return ESUCCESS;
}

int clock_detach(UNUSED dev_t *self)
{
    return ESUCCESS;
}

int clock_ioctl(dev_t *self, int ioctl, void *val, void **ret_val)
{
    int ret;
    dev_t *dev;
    dev_t *dev_child;
    uint32_t *id;
    
    switch (ioctl) {
    case IOCTL_UART_CLK_SET_EN:
    case IOCTL_UART_CLK_GET_EN:
    case IOCTL_UART_CLK_GET_FREQ:
    case IOCTL_UART_CLK_SET_FREQ:
        id = (uint32_t *) val;
        dev = kern_dev_select_name("uart", (*id));
        
        if (!dev)
            return ENODEV;
        
        dev_child = kern_dev_select_child(self, 0);
        
        if (!dev_child)
            return ENODEV;
        
        ret = kern_dev_ioctl(dev_child, ioctl, val, ret_val);
        break;
    default:
        return EIOCTL;
    }
    
    if (ret != ESUCCESS)
        return ret;
    
    return ESUCCESS;
}

int clock_init(void)
{
    dev_t *dev = NULL;
    int ret;
    
    dev = kern_dev_create(DEV_TYPE_CLK, 0, "clock", NULL, 0);
    
    if (!dev)
        return ENODEV;
    
    ret = kern_dev_op_attach(dev, clock_attach);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_detach(dev, clock_detach);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_ioctl(dev, clock_ioctl);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    return ESUCCESS;
}
