/**
 *
 * File Name: kern/kern_dev.c
 * Title    : Kernel
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-26
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
#include <string.h>
#include <errno.h>

#include <fifo.h>

#include <dev/init.h>

#include <kern/dev.h>

#define DEV_OPS_OPEN        0x00000001
#define DEV_OPS_CLOSE       0x00000002
#define DEV_OPS_WRITE       0x00000010
#define DEV_OPS_READ        0x00000020
#define DEV_OPS_IOCTL       0x00000100

#define DEV_FLAG_USED       0x00000001
#define DEV_FLAG_OPENED     0x00000010
#define DEV_FLAG_CLOSED     0x00000020

#define DEV_MAX             32

struct _kern_dev {
    int id;
    uint32_t class;
    int type;
    int block;
    uint32_t flags;
    uint32_t ops;
    void *conf;
    int (*op_open)(struct _kern_dev *);
    void (*op_close)(struct _kern_dev *);
    int (*op_write)(struct _kern_dev *, const uint8_t *, int);
    int (*op_read)(struct _kern_dev *, uint8_t *, int);
    int (*op_ioctl)(struct _kern_dev *, int, void *);
    fifo_t *fifo;
};

static struct _kern_dev *kern_devs;
static int kern_devs_size;
static int kern_devs_count;

struct _kern_dev *kern_dev_create(uint32_t d_class, int d_type, int d_block, void *d_conf)
{
    int i;
    struct _kern_dev *dev = NULL;
    fifo_t *fifo = NULL;
    
    if (kern_devs_count >= kern_devs_size)
        return NULL;
    
    for (i = 0; i < kern_devs_size; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->flags & DEV_FLAG_USED))
            break;
        else
            dev = NULL;
    }
    
    if (dev == NULL)
        return NULL;
    
    memset(dev, 0, sizeof(struct _kern_dev));
    dev->id = i;
    dev->class = d_class;
    dev->type = d_type;
    
    if (d_type == DEV_TYPE_BLOCK) {
        dev->block = d_block;
        fifo = fifo_init(dev->block);
        
        if (!fifo)
            return NULL;
        
        dev->fifo = fifo;
    } else {
        dev->block = 1;
        dev->fifo = NULL;
    }
    
    if (d_conf)
        dev->conf = d_conf;
    else
        dev->conf = NULL;
    
    dev->flags |= DEV_FLAG_USED;
    kern_devs_count++;
    return dev;
}

void kern_dev_free(struct _kern_dev *dev)
{
    if (!dev)
        return;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return;
    
    if (!(dev->ops & DEV_OPS_CLOSE))
        dev->op_close(dev);
    
    if (dev->type == DEV_TYPE_BLOCK)
        fifo_free(dev->fifo);
    
    memset(dev, 0, sizeof(struct _kern_dev));
}

int kern_dev_op_open(struct _kern_dev *dev, 
                     int (*op_open)(struct _kern_dev *))
{
    if (!dev)
        return EINVAL;
    
    if (!op_open)
        return EINVAL;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return ENODEV;
    
    dev->op_open = op_open;
    dev->ops |= DEV_OPS_OPEN;
    return ESUCCESS;
}

int kern_dev_op_close(struct _kern_dev *dev, 
                      void (*op_close)(struct _kern_dev *))
{
    if (!dev)
        return EINVAL;
    
    if (!op_close)
        return EINVAL;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return ENODEV;
    
    dev->op_close = op_close;
    dev->ops |= DEV_OPS_CLOSE;
    return ESUCCESS;
}

int kern_dev_op_write(struct _kern_dev *dev, 
                      int (*op_write)(struct _kern_dev *, const uint8_t *, int))
{
    if (!dev)
        return EINVAL;
    
    if (!op_write)
        return EINVAL;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return ENODEV;
    
    dev->op_write = op_write;
    dev->ops |= DEV_OPS_WRITE;
    return ESUCCESS;
}

int kern_dev_op_read(struct _kern_dev *dev, 
                     int (*op_read)(struct _kern_dev *, uint8_t *, int))
{
    if (!dev)
        return EINVAL;
    
    if (!op_read)
        return EINVAL;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return ENODEV;
    
    dev->op_read = op_read;
    dev->ops |= DEV_OPS_READ;
    return ESUCCESS;
}

int kern_dev_op_ioctl(struct _kern_dev *dev, 
                      int (*op_ioctl)(struct _kern_dev *, int, void *))
{
    if (!dev)
        return EINVAL;
    
    if (!op_ioctl)
        return EINVAL;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return ENODEV;
    
    dev->op_ioctl = op_ioctl;
    dev->ops |= DEV_OPS_IOCTL;
    return ESUCCESS;
}

void *kern_dev_config(struct _kern_dev *dev)
{
    if (!dev)
        return NULL;
    
    return dev->conf;
}

int kern_dev_open(struct _kern_dev *dev)
{
    if (!dev)
        return EINVAL;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return ENODEV;
    
    if (!(dev->ops & DEV_OPS_OPEN))
        return ENODEV;
    
    return dev->op_open(dev);
}

void kern_dev_close(struct _kern_dev *dev)
{
    if (!dev)
        return;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return;
    
    if (!(dev->ops & DEV_OPS_CLOSE))
        return;
    /* TODO: Flush buffer on block devices */
    dev->op_close(dev);
}

int kern_dev_write(struct _kern_dev *dev, const uint8_t *buf, int len)
{
    if (!dev)
        return EINVAL;
    
    if (!buf)
        return EINVAL;
    
    if (len < 1)
        return EINVAL;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return ENODEV;
    
    if (!(dev->ops & DEV_OPS_WRITE))
        return ENODEV;
    
    if (dev->type == DEV_TYPE_CHAR)
        return dev->op_write(dev, buf, len);
    
    /* TODO: block devices */
    return ESUCCESS;
}

int kern_dev_read(struct _kern_dev *dev, uint8_t *buf, int len)
{
    if (!dev)
        return EINVAL;
    
    if (!buf)
        return EINVAL;
    
    if (len < 1)
        return EINVAL;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return ENODEV;
    
    if (!(dev->ops & DEV_OPS_READ))
        return ENODEV;
    
    if (dev->type == DEV_TYPE_CHAR)
        return dev->op_read(dev, buf, len);
    
    /* TODO: block devices */
    return ESUCCESS;
}

int kern_dev_ioctl(struct _kern_dev *dev, int op, void *val)
{
    if (!dev)
        return EINVAL;
    
    if (!(dev->flags & DEV_FLAG_USED))
        return ENODEV;
    
    if (!(dev->ops & DEV_OPS_IOCTL))
        return ENODEV;
    
    return dev->op_ioctl(dev, op, val);
}

int kern_dev_write_class(uint32_t d_class, const uint8_t *buf, int len)
{
    int i;
    int ret;
    struct _kern_dev *dev;
    
    if (!(d_class & DEV_CLASS_STDOUT))
        return EINVAL;
    
    if (!buf)
        return EINVAL;
    
    if (len < 1)
        return EINVAL;
    
    for (i = 0; i < kern_devs_size; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->flags & DEV_FLAG_USED))
            continue;
        
        if (!(dev->class & DEV_CLASS_STDOUT))
            continue;
        
        ret = dev->op_write(dev, buf, len);
        
        if (ret != len)
            return EIOERR;
    }
    
    return ret;
}

int kern_dev_read_class(uint32_t d_class, uint8_t *buf, int len)
{
    int i;
    int ret;
    struct _kern_dev *dev;
    
    if (!(d_class & DEV_CLASS_STDIN))
        return EINVAL;
    
    if (!buf)
        return EINVAL;
    
    if (len < 1)
        return EINVAL;
    
    for (i = 0; i < kern_devs_size; i++) {
        dev = &kern_devs[i];
        
        if (!(dev->flags & DEV_FLAG_USED))
            continue;
        
        if (!(dev->class & DEV_CLASS_STDIN))
            continue;
        
        ret = dev->op_read(dev, buf, len);
        
        if (ret != len)
            return EIOERR;
    }
    
    return ret;
}

int kern_dev_init(void)
{
    int len;
    int ret;
    
    len = (sizeof(struct _kern_dev) * DEV_MAX);
    kern_devs = (struct _kern_dev *) malloc(len);
    
    if (!kern_devs)
        return ENOMEM;
    
    memset(kern_devs, 0, len);
    kern_devs_size = DEV_MAX;
    kern_devs_count = 0;
    ret = dev_init();
    
    if (ret != ESUCCESS)
        return ret;
    
    return ESUCCESS;
}
