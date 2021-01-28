/**
 *
 * File Name: kern/kern_dev.c
 * Title    : Kernel Device Subsystem
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-26
 * Modified : 2021-02-28
 * Revised  : 
 * Version  : 0.2.0.0
 * License  : ISC (see LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fifo.h>

#include <dev/init.h>

#include <kern/dev.h>

#define DEV_FLAG_VALID      0x00000001
#define DEV_FLAG_ATTACHED   0x00000002
#define DEV_FLAG_ACTIVE     0x00000004
#define DEV_FLAG_OPENED     0x00000010
#define DEV_FLAG_BUSY       0x00000020
#define DEV_FLAG_ERR        0x10000000

#define DEV_OPS_OPEN        0x00000001
#define DEV_OPS_CLOSE       0x00000002
#define DEV_OPS_WR          0x00000100
#define DEV_OPS_RD          0x00000200
#define DEV_OPS_WR_ADDR     0x00000400
#define DEV_OPS_RD_ADDR     0x00000800
#define DEV_OPS_FLUSH       0x00001000
#define DEV_OPS_IOCTL       0x00010000

#define DEV_NAME_MAX        256
#define DEV_PARENT_MAX      64
#define DEV_CHILDS_MAX      64
#define DEV_REQUIRE_MAX     64

#define DEV_MAX             512

struct _kern_dev {
    uint32_t d_id;
    char d_name[DEV_NAME_MAX];
    uint32_t d_subid;
    uint32_t d_parentnr;
    struct _kern_dev *d_parent[DEV_PARENT_MAX];
    uint32_t d_reqnr;
    struct _kern_dev *d_require[DEV_REQUIRE_MAX];
    uint32_t d_childnr;
    struct _kern_dev *d_childs[DEV_CHILDS_MAX];
    uint32_t d_type;
    uint32_t d_caps;
    uint32_t d_blocksz;
    uint32_t d_flags;
    uint32_t d_err;
    uint32_t d_ops;
    fifo_t *d_fifo;
    void *d_conf;
    int (*d_op_attach)(struct _kern_dev *);
    int (*d_op_detach)(struct _kern_dev *);
    int (*d_op_open)(struct _kern_dev *);
    int (*d_op_close)(struct _kern_dev *);
    size_t (*d_op_wr)(struct _kern_dev *, const uint8_t *, size_t);
    size_t (*d_op_rd)(struct _kern_dev *, uint8_t *, size_t);
    size_t (*d_op_wr_addr)(struct _kern_dev *, uint64_t, uint64_t, const uint8_t *, size_t);
    size_t (*d_op_rd_addr)(struct _kern_dev *, uint64_t, uint64_t, uint8_t *, size_t);
    int (*d_op_flush)(struct _kern_dev *);
    int (*d_op_ioctl)(struct _kern_dev *, int, void *, void **);
};

static struct _kern_dev *kern_devs;
static int kern_devs_num;
static int kern_devs_cnt;
static int kern_devs_id;

int kern_dev_init(void)
{
    int len;
    int ret;
    
    len = (sizeof(struct _kern_dev) * DEV_MAX);
    kern_devs = (struct _kern_dev *) malloc(len);
    
    if (!kern_devs)
        return ENOMEM;
    
    memset(kern_devs, 0, len);
    kern_devs_num = DEV_MAX;
    kern_devs_cnt = 0;
    kern_devs_id = 0;
    ret = dev_init();
    
    if (ret != ESUCCESS)
        return ret;
    
    return ESUCCESS;
}

static uint32_t dev_find_name_subid_high(const char *d_name)
{
    int i;
    int ret;
    int cur;
    struct _kern_dev *dev;
    
    ret = 0;
    cur = 0;
    
    for (i = 0; i < kern_devs_num; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->d_flags & DEV_FLAG_VALID))
            continue;
        
        if (strcmp(d_name, dev->d_name) == 0) {
            cur = dev->d_subid;
            
            if (cur > ret)
                ret = cur;
        }
    }
    
    return ret;
}

static struct _kern_dev *dev_get_subid_name(const char *d_name, uint32_t d_subid)
{
    int i;
    struct _kern_dev *dev;
    
    for (i = 0; i < kern_devs_num; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->d_flags & DEV_FLAG_VALID))
            continue;
        
        if (strcmp(d_name, dev->d_name) != 0)
            continue;
        
        if (dev->d_subid == d_subid)
            return dev;
    }
    
    return NULL;
}

struct _kern_dev *kern_dev_create(uint32_t d_type, uint32_t d_caps, const char *d_name, struct _kern_dev *d_parent, uint32_t d_blocksz)
{
    int i;
    struct _kern_dev *dev;
    fifo_t *fifo;
    
    if (kern_devs_cnt >= kern_devs_num)
        return NULL;
    
    for (i = 0; i < kern_devs_num; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->d_flags & DEV_FLAG_VALID))
            break;
    }
    
    memset(dev, 0, sizeof(struct _kern_dev));
    dev->d_type = d_type;
    dev->d_caps = d_caps;
    
    if (strlen(d_name) >= DEV_NAME_MAX)
        return NULL;
    
    strcpy(dev->d_name, d_name);
    dev->d_subid = dev_find_name_subid_high(dev->d_name);
    
    if (d_parent) {
        dev->d_parent[0] = d_parent;
        dev->d_parentnr = 1;
    }
    
    if (dev->d_caps & DEV_CAPS_BLK) {
        if (d_blocksz > 1) {
            fifo = fifo_init(d_blocksz);
            
            if (!fifo)
                return NULL;
            
            dev->d_fifo = fifo;
            dev->d_blocksz = d_blocksz;
        }
    } else {
        dev->d_fifo = NULL;
        dev->d_blocksz = d_blocksz;
    }
    
    dev->d_id = kern_devs_id;
    kern_devs_id++;
    dev->d_flags |= DEV_FLAG_VALID;
    return dev;
}

int kern_dev_delete(struct _kern_dev *dev)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    if (dev->d_flags & DEV_FLAG_VALID)
        return ENODEV;
    
    if (dev->d_flags & DEV_FLAG_ATTACHED) {
        if (dev->d_flags & DEV_FLAG_OPENED) {
            if (dev->d_flags & DEV_FLAG_BUSY)
                return EBUSY;
            
            if (dev->d_ops & DEV_OPS_CLOSE)
                ret = dev->d_op_close(dev);
            
            if (ret != ESUCCESS)
                return ret;
        }
    }
    
    memset(dev, 0, sizeof(struct _kern_dev));
    return ESUCCESS;
}

int kern_dev_set_config(struct _kern_dev *dev, void *d_conf)
{
    if (!dev)
        return EINVAL;
    
    if (!d_conf)
        return EINVAL;
    
    dev->d_conf = d_conf;
    return ESUCCESS;
}

void *kern_dev_get_config(struct _kern_dev *dev)
{
    if (!dev)
        return NULL;
    
    return dev->d_conf;
}

int kern_dev_add_child(struct _kern_dev *dev, struct _kern_dev *dev_child)
{
    uint32_t i;
    
    if (!dev)
        return EINVAL;
    
    if (!dev_child)
        return EINVAL;
    
    for (i = 0; i < DEV_CHILDS_MAX; i++) {
        if (dev->d_childs[i] == NULL) {
            dev->d_childs[i] = dev_child;
            dev->d_childnr++;
            break;
        }
    }
    
    return ESUCCESS;
}

int kern_dev_del_child(struct _kern_dev *dev, struct _kern_dev *dev_child)
{
    uint32_t i;
    
    if (!dev)
        return EINVAL;
    
    if (!dev_child)
        return EINVAL;
    
    if (!dev->d_childnr)
        return ESUCCESS;
    
    for (i = 0; i < DEV_CHILDS_MAX; i++) {
        if (dev->d_childs[i] == dev_child) {
            dev->d_childs[i] = NULL;
            dev->d_childnr--;
            break;
        }
    }
    
    return ESUCCESS;
}

int kern_dev_add_parent(struct _kern_dev *dev, struct _kern_dev *dev_parent)
{
    uint32_t i;
    
    if (!dev)
        return EINVAL;
    
    if (!dev_parent)
        return EINVAL;
    
    for (i = 0; i < DEV_PARENT_MAX; i++) {
        if (dev->d_parent[i] == NULL) {
            dev->d_parent[i] = dev_parent;
            dev->d_parentnr++;
            break;
        }
    }
    
    return ESUCCESS;
}

int kern_dev_del_parent(struct _kern_dev *dev, struct _kern_dev *dev_parent)
{
    uint32_t i;
    
    if (!dev)
        return EINVAL;
    
    if (!dev_parent)
        return EINVAL;
    
    if (!dev->d_parentnr)
        return ESUCCESS;
    
    for (i = 0; i < DEV_PARENT_MAX; i++) {
        if (dev->d_parent[i] == dev_parent) {
            dev->d_parent[i] = NULL;
            dev->d_parentnr--;
            break;
        }
    }
    
    return ESUCCESS;
}

int kern_dev_add_require(struct _kern_dev *dev, struct _kern_dev *dev_req)
{
    uint32_t i;
    
    if (!dev)
        return EINVAL;
    
    if (!dev_req)
        return EINVAL;
    
    for (i = 0; i < DEV_REQUIRE_MAX; i++) {
        if (dev->d_require[i] == NULL) {
            dev->d_require[i] = dev_req;
            dev->d_reqnr++;
            break;
        }
    }
    
    return ESUCCESS;
}

int kern_dev_del_require(struct _kern_dev *dev, struct _kern_dev *dev_req)
{
    uint32_t i;
    
    if (!dev)
        return EINVAL;
    
    if (!dev_req)
        return EINVAL;
    
    if (!dev->d_reqnr)
        return ESUCCESS;
    
    for (i = 0; i < DEV_REQUIRE_MAX; i++) {
        if (dev->d_require[i] == dev_req) {
            dev->d_require[i] = NULL;
            dev->d_reqnr--;
            break;
        }
    }
    
    return ESUCCESS;
}

int kern_dev_attach_all(void)
{
    int i;
    int ret;
    struct _kern_dev *dev;
    
    for (i = 0; i < kern_devs_num; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->d_flags & DEV_FLAG_VALID))
            continue;
        
        ret = dev->d_op_attach(dev);
        
        if (ret != ESUCCESS)
            return ret;
    }
    
    return ESUCCESS;
}

int kern_dev_attach(struct _kern_dev *dev)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    ret = dev->d_op_attach(dev);
    
    if (ret != ESUCCESS)
        return ret;
    
    return ESUCCESS;
}

uint32_t kern_dev_error(struct _kern_dev *dev)
{
    if (!dev)
        return EINVAL;
    
    return dev->d_err;
}

int kern_dev_find_name(const char *d_name, struct _kern_dev ***ret_devs)
{
    int i;
    int j;
    struct _kern_dev *dev;
    struct _kern_dev **ret;
    
    if (!d_name)
        return EINVAL;
    
    if (strlen(d_name) >= DEV_NAME_MAX)
        return EINVAL;
    
    if (!ret_devs)
        return EINVAL;
    
    ret = (struct _kern_dev **) malloc(sizeof(struct _kern_dev *) * DEV_MAX);
    
    if (!ret)
        return ENOMEM;
    
    j = 0;
    
    for (i = 0; i < kern_devs_num; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->d_flags & DEV_FLAG_VALID))
            continue;
        
        if (strcmp(d_name, dev->d_name) == 0)
            ret[j++] = dev;
    }
    
    (*ret_devs) = ret;
    return j;
}

int kern_dev_find_type(uint32_t d_type, struct _kern_dev ***ret_devs)
{
    int i;
    int j;
    struct _kern_dev *dev;
    struct _kern_dev **ret;
    
    if (!ret_devs)
        return EINVAL;
    
    ret = (struct _kern_dev **) malloc(sizeof(struct _kern_dev *) * DEV_MAX);
    
    if (!ret)
        return ENOMEM;
    
    j = 0;
    
    for (i = 0; i < kern_devs_num; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->d_flags & DEV_FLAG_VALID))
            continue;
        
        if (dev->d_type == d_type)
            ret[j++] = dev;
    }
    
    (*ret_devs) = ret;
    return j;
}

int kern_dev_find_caps(uint32_t d_caps, struct _kern_dev ***ret_devs)
{
    int i;
    int j;
    struct _kern_dev *dev;
    struct _kern_dev **ret;
    
    if (!ret_devs)
        return EINVAL;
    
    ret = (struct _kern_dev **) malloc(sizeof(struct _kern_dev *) * DEV_MAX);
    
    if (!ret)
        return ENOMEM;
    
    j = 0;
    
    for (i = 0; i < kern_devs_num; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->d_flags & DEV_FLAG_VALID))
            continue;
        
        if (dev->d_caps == d_caps)
            ret[j++] = dev;
    }
    
    (*ret_devs) = ret;
    return j;
}

struct _kern_dev *kern_dev_select_name(const char *d_name, uint32_t d_subid)
{
    if (!d_name)
        return NULL;
    
    if (strlen(d_name) >= DEV_NAME_MAX)
        return NULL;
    
    
    return dev_get_subid_name(d_name, d_subid);
}

struct _kern_dev *kern_dev_select_require(struct _kern_dev *dev, uint32_t d_subid)
{
    uint32_t i;
    struct _kern_dev *dev_req;
    
    if (!dev)
        return NULL;
    
    for (i = 0; i < dev->d_reqnr; i++) {
        dev_req = dev->d_require[i];
        
        if (dev_req->d_subid == d_subid)
            return dev_req;
    }
    
    return NULL;
}

struct _kern_dev *kern_dev_select_child(struct _kern_dev *dev, uint32_t d_subid)
{
    uint32_t i;
    struct _kern_dev *dev_req;
    
    if (!dev)
        return NULL;
    
    for (i = 0; i < dev->d_childnr; i++) {
        dev_req = dev->d_childs[i];
        
        if (dev_req->d_subid == d_subid)
            return dev_req;
    }
    
    return NULL;
}

struct _kern_dev *kern_dev_select_parent(struct _kern_dev *dev, uint32_t d_subid)
{
    uint32_t i;
    struct _kern_dev *dev_req;
    
    if (!dev)
        return NULL;
    
    for (i = 0; i < dev->d_parentnr; i++) {
        dev_req = dev->d_parent[i];
        
        if (dev_req->d_subid == d_subid)
            return dev_req;
    }
    
    return NULL;
}

int kern_dev_open(struct _kern_dev *dev)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    if (!(dev->d_flags & DEV_FLAG_VALID))
        return ENODEV;
    
    if (!(dev->d_flags & DEV_FLAG_ATTACHED)) {
        ret = dev->d_op_attach(dev);
        
        if (ret != ESUCCESS)
            return ret;
    }
    
    if (dev->d_ops & DEV_OPS_OPEN) {
        if (!(dev->d_flags & DEV_FLAG_OPENED)) {
            ret = dev->d_op_open(dev);
            
            if (ret != ESUCCESS)
                return ret;
        }
    }
    
    return ESUCCESS;
}

int kern_dev_close(struct _kern_dev *dev)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    if (!(dev->d_flags & DEV_FLAG_VALID))
        return ENODEV;
    
    if ((dev->d_flags & DEV_FLAG_ATTACHED))
        return ESUCCESS;
    
    if (dev->d_ops & DEV_OPS_OPEN) {
        if (dev->d_flags & DEV_FLAG_OPENED) {
            ret = dev->d_op_close(dev);
            
            if (ret != ESUCCESS)
                return ret;
        }
    }
    
    return ESUCCESS;
}

size_t kern_dev_wr(struct _kern_dev *dev, const uint8_t *buf, size_t len)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    if (!buf)
        return EINVAL;
    
    if (!(dev->d_flags & DEV_FLAG_VALID)) {
        dev->d_err = ENODEV;
        return 0;
    }
    
    if (!(dev->d_flags & DEV_FLAG_ATTACHED)) {
        ret = dev->d_op_attach(dev);
        
        if (ret != ESUCCESS) {
            dev->d_err = ret;
            return 0;
        }
    }
    
    if (dev->d_ops & DEV_OPS_OPEN) {
        if (!(dev->d_flags & DEV_FLAG_OPENED)) {
            ret = dev->d_op_open(dev);
            
            if (ret != ESUCCESS) {
            dev->d_err = ret;
            return 0;
            }
        }
    }
    
    if (dev->d_ops & DEV_OPS_WR)
        return dev->d_op_wr(dev, buf, len);
    
    return 0;
}

size_t kern_dev_rd(struct _kern_dev *dev, uint8_t *buf, size_t len)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    if (!buf)
        return EINVAL;
    
    if (!(dev->d_flags & DEV_FLAG_VALID)) {
        dev->d_err = ENODEV;
        return 0;
    }
    
    if (!(dev->d_flags & DEV_FLAG_ATTACHED)) {
        ret = dev->d_op_attach(dev);
        
        if (ret != ESUCCESS) {
            dev->d_err = ret;
            return 0;
        }
    }
    
    if (dev->d_ops & DEV_OPS_OPEN) {
        if (!(dev->d_flags & DEV_FLAG_OPENED)) {
            ret = dev->d_op_open(dev);
            
            if (ret != ESUCCESS) {
            dev->d_err = ret;
            return 0;
            }
        }
    }
    
    if (dev->d_ops & DEV_OPS_RD)
        return dev->d_op_rd(dev, buf, len);
    
    return 0;
}

size_t kern_dev_wr_addr(struct _kern_dev *dev, uint64_t addr, uint64_t off, const uint8_t *buf, size_t len)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    if (!buf)
        return EINVAL;
    
    if (!(dev->d_flags & DEV_FLAG_VALID)) {
        dev->d_err = ENODEV;
        return 0;
    }
    
    if (!(dev->d_flags & DEV_FLAG_ATTACHED)) {
        ret = dev->d_op_attach(dev);
        
        if (ret != ESUCCESS) {
            dev->d_err = ret;
            return 0;
        }
    }
    
    if (dev->d_ops & DEV_OPS_OPEN) {
        if (!(dev->d_flags & DEV_FLAG_OPENED)) {
            ret = dev->d_op_open(dev);
            
            if (ret != ESUCCESS) {
            dev->d_err = ret;
            return 0;
            }
        }
    }
    
    if (dev->d_ops & DEV_OPS_WR_ADDR)
        return dev->d_op_wr_addr(dev, addr, off, buf, len);
    
    return 0;
}

size_t kern_dev_rd_addr(struct _kern_dev *dev, uint64_t addr, uint64_t off, uint8_t *buf, size_t len)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    if (!buf)
        return EINVAL;
    
    if (!(dev->d_flags & DEV_FLAG_VALID)) {
        dev->d_err = ENODEV;
        return 0;
    }
    
    if (!(dev->d_flags & DEV_FLAG_ATTACHED)) {
        ret = dev->d_op_attach(dev);
        
        if (ret != ESUCCESS) {
            dev->d_err = ret;
            return 0;
        }
    }
    
    if (dev->d_ops & DEV_OPS_OPEN) {
        if (!(dev->d_flags & DEV_FLAG_OPENED)) {
            ret = dev->d_op_open(dev);
            
            if (ret != ESUCCESS) {
            dev->d_err = ret;
            return 0;
            }
        }
    }
    
    if (dev->d_ops & DEV_OPS_RD_ADDR)
        return dev->d_op_rd_addr(dev, addr, off, buf, len);
    
    return 0;
}

int kern_dev_flush(struct _kern_dev *dev)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    if (!(dev->d_flags & DEV_FLAG_VALID))
        return ENODEV;
    
    if (!(dev->d_flags & DEV_FLAG_ATTACHED)) {
        ret = dev->d_op_attach(dev);
        
        if (ret != ESUCCESS)
            return ret;
    }
    
    if (dev->d_ops & DEV_OPS_FLUSH) {
        if (!(dev->d_flags & DEV_FLAG_OPENED)) {
            return ESUCCESS;
        } else {
            ret = dev->d_op_flush(dev);
            
            if (ret != ESUCCESS)
                return ret;
        }
    }
    
    return ESUCCESS;
}

int kern_dev_ioctl(struct _kern_dev *dev, int ioctl, void *val, void **ret_val)
{
    int ret;
    
    if (!dev)
        return EINVAL;
    
    if (!(dev->d_flags & DEV_FLAG_VALID)) {
        dev->d_err = ENODEV;
        return 0;
    }
    
    if (!(dev->d_flags & DEV_FLAG_VALID))
        return ENODEV;
    
    if (!(dev->d_flags & DEV_FLAG_ATTACHED)) {
        ret = dev->d_op_attach(dev);
        
        if (ret != ESUCCESS)
            return ret;
    }
    
    if (dev->d_ops & DEV_OPS_IOCTL) {
        ret = dev->d_op_ioctl(dev, ioctl, val, ret_val);
        
        if (ret != ESUCCESS)
            return ret;
    }
    
    return ESUCCESS;
}

int kern_dev_op_attach(struct _kern_dev *dev, int (*d_op_attach)(struct _kern_dev *dev))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_attach)
        return EINVAL;
    
    dev->d_op_attach = d_op_attach;
    return ESUCCESS;
}

int kern_dev_op_detach(struct _kern_dev *dev, int (*d_op_detach)(struct _kern_dev *dev))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_detach)
        return EINVAL;
    
    dev->d_op_detach = d_op_detach;
    return ESUCCESS;
}

int kern_dev_op_open(struct _kern_dev *dev, int (*d_op_open)(struct _kern_dev *dev))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_open)
        return EINVAL;
    
    dev->d_op_open = d_op_open;
    dev->d_ops |= DEV_OPS_OPEN;
    return ESUCCESS;
}

int kern_dev_op_close(struct _kern_dev *dev, int (*d_op_close)(struct _kern_dev *dev))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_close)
        return EINVAL;
    
    dev->d_op_close = d_op_close;
    dev->d_ops |= DEV_OPS_CLOSE;
    return ESUCCESS;
}

int kern_dev_op_wr(struct _kern_dev *dev, size_t (*d_op_wr)(struct _kern_dev *, const uint8_t *, size_t))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_wr)
        return EINVAL;
    
    dev->d_op_wr = d_op_wr;
    dev->d_ops |= DEV_OPS_WR;
    return ESUCCESS;
}

int kern_dev_op_rd(struct _kern_dev *dev, size_t (*d_op_rd)(struct _kern_dev *, uint8_t *, size_t))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_rd)
        return EINVAL;
    
    dev->d_op_rd = d_op_rd;
    dev->d_ops |= DEV_OPS_RD;
    return ESUCCESS;
}

int kern_dev_op_wr_addr(struct _kern_dev *dev, size_t (*d_op_wr_addr)(struct _kern_dev *, uint64_t, uint64_t, const uint8_t *, size_t))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_wr_addr)
        return EINVAL;
    
    dev->d_op_wr_addr = d_op_wr_addr;
    dev->d_ops |= DEV_OPS_WR_ADDR;
    return ESUCCESS;
}

int kern_dev_op_rd_addr(struct _kern_dev *dev, size_t (*d_op_rd_addr)(struct _kern_dev *, uint64_t, uint64_t, uint8_t *, size_t))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_rd_addr)
        return EINVAL;
    
    dev->d_op_rd_addr = d_op_rd_addr;
    dev->d_ops |= DEV_OPS_RD_ADDR;
    return ESUCCESS;
}

int kern_dev_op_flush(struct _kern_dev *dev, int (*d_op_flush)(struct _kern_dev *dev))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_flush)
        return EINVAL;
    
    dev->d_op_flush = d_op_flush;
    dev->d_ops |= DEV_OPS_FLUSH;
    return ESUCCESS;
}

int kern_dev_op_ioctl(struct _kern_dev *dev, int (*d_op_ioctl)(struct _kern_dev *dev, int, void *, void **))
{
    if (!dev)
        return EINVAL;
    
    if (!d_op_ioctl)
        return EINVAL;
    
    dev->d_op_ioctl = d_op_ioctl;
    dev->d_ops |= DEV_OPS_IOCTL;
    return ESUCCESS;
}
