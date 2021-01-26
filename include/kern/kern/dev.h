/**
 *
 * File Name: include/kern/kern/dev.h
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

#ifndef ROCK64_KERN_KERN_DEV_H
#define ROCK64_KERN_KERN_DEV_H

#include <stdint.h>

/* Device classes */
#define DEV_CLASS_STDIN     0x00000001
#define DEV_CLASS_STDOUT    0x00000002

/* Device type */
#define DEV_TYPE_CHAR       0
#define DEV_TYPE_BLOCK      1

struct _kern_dev;

typedef struct _kern_dev dev_t;

extern int kern_dev_init(void);

/* Device creation */
extern dev_t *kern_dev_create(uint32_t d_class, int d_type, int d_block, void *d_conf);
extern void kern_dev_free(dev_t *dev);

/* Device configuration */
extern int kern_dev_op_open(dev_t *dev, int (*op_open)(dev_t *));
extern int kern_dev_op_close(dev_t *dev, void (*op_close)(dev_t *));
extern int kern_dev_op_write(dev_t *dev, int (*op_write)(dev_t *, const uint8_t *, int));
extern int kern_dev_op_read(dev_t *dev, int (*op_read)(dev_t *, uint8_t *, int));
extern int kern_dev_op_ioctl(dev_t *dev, int (*op_ioctl)(dev_t *, int, void *));
extern void *kern_dev_config(dev_t *dev);

/* Generic device operations */
extern int kern_dev_open(dev_t *dev);
extern void kern_dev_close(dev_t *dev);
extern int kern_dev_write(dev_t *dev, const uint8_t *buf, int len);
extern int kern_dev_read(dev_t *dev, uint8_t *buf, int len);
extern int kern_dev_ioctl(dev_t *dev, int op, void *val);

/* Device operations by class */
extern int kern_dev_write_class(uint32_t d_class, const uint8_t *buf, int len);

#endif
