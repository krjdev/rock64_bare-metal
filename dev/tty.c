/**
 *
 * File Name: dev/tty.c
 * Title    : TTY Frontend Driver
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-29
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

size_t tty_wr(dev_t *self, const uint8_t *buf, size_t len)
{
    size_t ret;
    int err;
    dev_t *dev = NULL;
    
    dev = kern_dev_select_back(self, 0);
    
    if (!dev)
        return 0;
    
    ret = kern_dev_wr(dev, buf, len);
    
    if (ret != len) {
        err = kern_dev_get_error(dev);
        kern_dev_set_error(self, err);
    }
    
    return ret;
}

size_t tty_rd(dev_t *self, uint8_t *buf, size_t len)
{
    size_t ret;
    int err;
    dev_t *dev = NULL;
    
    dev = kern_dev_select_back(self, 0);
    
    if (!dev)
        return 0;
    
    ret = kern_dev_rd(dev, buf, len);
    err = kern_dev_get_error(dev);
    kern_dev_set_error(self, err);
    return ret;
}

int tty_attach(UNUSED dev_t *self)
{
    return ESUCCESS;
}

int tty_detach(UNUSED dev_t *self)
{
    return ESUCCESS;
}

int tty_init(void)
{
    dev_t *dev = NULL;
    int ret;
    
    dev = kern_dev_create(DEV_TYPE_TTY, DEV_CAPS_CHR, "tty", NULL, 0);
    
    if (!dev)
        return ENODEV;
    
    ret = kern_dev_op_attach(dev, tty_attach);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_detach(dev, tty_detach);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_wr(dev, tty_wr);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_rd(dev, tty_rd);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    return ESUCCESS;
}
