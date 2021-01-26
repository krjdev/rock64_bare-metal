/**
 *
 * File Name: include/kern/fifo.h
 * Title    : Kernel Library
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

#ifndef ROCK64_KERN_FIFO_H
#define ROCK64_KERN_FIFO_H

#include <stdint.h>

struct _fifo;
typedef struct _fifo fifo_t;

extern fifo_t *fifo_init(int len);
extern void fifo_free(fifo_t *fifo);
extern int fifo_enqueue(fifo_t *fifo, uint8_t data);
extern int fifo_dequeue(fifo_t *fifo, uint8_t *data);
extern int fifo_get_len(fifo_t *fifo);
extern int fifo_get_num(fifo_t *fifo);

#endif
