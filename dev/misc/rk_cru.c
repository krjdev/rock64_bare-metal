/**
 *
 * File Name: dev/rk_cru.c
 * Title    : Rockchip RK3328 Clock and Reset Controller Driver
 * Project  : PINE64 ROCK64 Bare-Metal Example
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-26
 * Modified : 2021-01-28
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
#include <stdint.h>
#include <stdlib.h>
#include <ioctl.h>
#include <compiler.h>

#include <dev/mmio.h>

#include <kern/dev.h>
#include <kern/mem.h>

#include <dev/uart/ioctl.h>

#define RK_CRU_BASE                     0xFF440000
#define RK_CRU_SIZE                     0x10000

#define RK_CRU_GLB_SRST_FST             0x9C
#define RK_CRU_GLB_SRST_FST_MAGIC       0xFDB9

struct _rk_cru {
    struct _kern_mem r_mem;
    dev_t *r_simplebus;
};

int rk_cru_sys_reset(dev_t *self)
{
    size_t ret;
    struct _rk_cru *rk_cru = NULL;
    uint32_t val[1];
    
    rk_cru = (struct _rk_cru *) kern_dev_get_config(self);
    
    if (!rk_cru)
        return ENODEV;
    
    val[0] = RK_CRU_GLB_SRST_FST_MAGIC;
    ret = kern_dev_wr_addr(rk_cru->r_simplebus, 
                           rk_cru->r_mem.m_paddr, 
                           RK_CRU_GLB_SRST_FST, 
                           (uint8_t *) val, 
                           4);
    
    if (ret != 4)
        return kern_dev_error(rk_cru->r_simplebus);
    
    return ESUCCESS;
}

int rk_cru_ioctl(dev_t *self, int ioctl, UNUSED void *val, UNUSED void **ret_val)
{
    int ret;
    
    if (!self)
        return ENODEV;
    
    switch (ioctl) {
    case IOCTL_SYS_RST_SET_EN:
        ret = rk_cru_sys_reset(self);
        break;
    default:
        return EIOCTL;
    }
    
    if (ret != ESUCCESS)
        return ret;
    
    return ESUCCESS;
}

int rk_cru_attach(UNUSED dev_t *self)
{
    return ESUCCESS;
}

int rk_cru_detach(UNUSED dev_t *self)
{
    return ESUCCESS;
}

int rk_cru_init(void)
{
    int ret;
    dev_t *dev = NULL;
    dev_t *dev_parent_clk = NULL;
    dev_t *dev_parent_rst = NULL;
    dev_t *dev_require = NULL;
    struct _rk_cru *rk_cru = NULL;
    
    dev_require = kern_dev_select_name("simplebus", 0);
    
    if (!dev_require)
        return ENODEV;
    
    dev_parent_clk = kern_dev_select_name("clock", 0);
    
    if (!dev_parent_clk)
        return ENODEV;
    
    dev_parent_rst = kern_dev_select_name("reset", 0);
    
    if (!dev_parent_rst)
        return ENODEV;
    
    dev = kern_dev_create(DEV_TYPE_MSC, 0, "rk_cru", NULL, 0);
    
    if (!dev)
        return ENODEV;
    
    rk_cru = (struct _rk_cru *) malloc(sizeof(struct _rk_cru));
    
    if (!rk_cru) {
        kern_dev_delete(dev);
        return ENOMEM;
    }
    
    ret = kern_dev_op_attach(dev, &rk_cru_attach);
    
    if (ret != ESUCCESS) {
        free(rk_cru);
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_detach(dev, &rk_cru_detach);
    
    if (ret != ESUCCESS) {
        free(rk_cru);
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_op_ioctl(dev, &rk_cru_ioctl);
    
    if (ret != ESUCCESS) {
        free(rk_cru);
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_add_parent(dev, dev_parent_clk);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_add_child(dev_parent_clk, dev);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_add_parent(dev, dev_parent_rst);
    
    if (ret != ESUCCESS) {
        kern_dev_delete(dev);
        return ret;
    }
    
    ret = kern_dev_add_child(dev_parent_rst, dev);
    
    if (ret != ESUCCESS) {
        kern_dev_del_child(dev_parent_clk, dev);
        kern_dev_delete(dev);
        return ret;
    }
    
    rk_cru->r_mem.m_paddr = RK_CRU_BASE;
    rk_cru->r_mem.m_psize = RK_CRU_SIZE;
    rk_cru->r_simplebus = dev_require;
    ret = kern_dev_set_config(dev, (void *) rk_cru);
    
    if (ret != ESUCCESS) {
        kern_dev_del_child(dev_parent_clk, dev);
        kern_dev_del_child(dev_parent_rst, dev);
        free(rk_cru);
        kern_dev_delete(dev);
        return ret;
    }
    
    return ESUCCESS;
}
