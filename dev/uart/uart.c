/**
 *
 * File Name: dev/uart/uart.c
 * Title    : Generic UART device
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
#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include <compiler.h>

#include <kern/dev.h>

size_t uart_wr(dev_t *self, const uint8_t *buf, size_t len)
{
    dev_t *dev_child = NULL;
    
    dev_child = kern_dev_select_child(self, 0);
    
    if (!dev_child)
        return 0;
    
    return kern_dev_wr(dev_child, buf, len);
}

size_t uart_rd(dev_t *self, uint8_t *buf, size_t len)
{
    dev_t *dev_child = NULL;
    
    dev_child = kern_dev_select_child(self, 0);
    
    if (!dev_child)
        return 0;
    
    return kern_dev_rd(dev_child, buf, len);
}

int uart_attach(UNUSED dev_t *self)
{
    return ESUCCESS;
}

int uart_detach(UNUSED dev_t *self)
{
    return ESUCCESS;
}

int uart_init(void)
{
    dev_t *dev = NULL;
    dev_t *dev_parent = NULL;
    int ret;
    
    dev_parent = kern_dev_select_name("tty", 0);
    
    if (!dev_parent)
        return ENODEV;
    
    dev = kern_dev_create(DEV_TYPE_COM, DEV_CAPS_CHR, "uart", dev_parent, 0);
    
    if (!dev)
        return ENODEV;
    
    ret = kern_dev_op_attach(dev, uart_attach);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_detach(dev, uart_detach);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_wr(dev, uart_wr);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_rd(dev, uart_rd);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    return ESUCCESS;
}
