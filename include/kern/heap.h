/**
 *
 * File Name: include/kern/heap.h
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

#ifndef ROCK64_KERN_HEAP_H
#define ROCK64_KERN_HEAP_H

extern void heap_init(void);
extern void *heap_alloc(unsigned int size);
extern void heap_free(void *ptr);
extern int heap_size(void *ptr);

#endif
