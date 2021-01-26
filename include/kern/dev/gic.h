/**
 *
 * File Name: include/kern/dev/gic.h
 * Title    : Global Interrupt Controller
 * Project  : PINE64 ROCK64 Bare-Metal Example
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

#ifndef ROCK64_KERN_DEV_GIC_H
#define ROCK64_KERN_DEV_GIC_H

extern int gic_init(void);
extern void gic_intr_enable(int irq_nr);
extern void gic_intr_set_prior(int irq_nr, uint8_t prior);
extern void gic_intr_set_group(int irq_nr, int group);

#endif
