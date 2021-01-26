/**
 *
 * File Name: libkern/fifo.c
 * Title    : Kernel Library
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
#include <fifo.h>

struct _fifo {
    int f_len;
    int f_num;
    uint8_t *f_p;
    int f_idxr;
    int f_idxw;
};

fifo_t *fifo_init(int len)
{
    fifo_t *f;
    uint8_t *p;
    
    if (len < 1)
        return NULL;
    
    p = (uint8_t *) malloc(len);
    
    if (!p)
        return NULL;
    
    f = (fifo_t *) malloc(sizeof(fifo_t));
    
    if (!f) {
        free(p);
        return NULL;
    }
    
    f->f_len = len;
    f->f_num = 0;
    f->f_p = p;
    f->f_idxw = 0;
    f->f_idxr = -1;
    return f;
}

void fifo_free(fifo_t *fifo)
{
    if (!fifo)
        return;
    
    if (fifo->f_p)
        free(fifo->f_p);
    
    fifo->f_p = NULL;
    free(fifo);
}

int fifo_enqueue(fifo_t *fifo, uint8_t data)
{
    if (!fifo)
        return -1;
    
    if (!fifo->f_p)
        return -1;
    
    if (fifo->f_num < fifo->f_len) {
        fifo->f_p[fifo->f_idxw] = data;
        fifo->f_num++;
        
        if (fifo->f_idxw < (fifo->f_len - 1))
            fifo->f_idxw++;
        else
            fifo->f_idxw = 0;
        
        if (fifo->f_idxr == -1)
            fifo->f_idxr = 0;
    } else
        return -1;
    
    return 0;
}

int fifo_dequeue(fifo_t *fifo, uint8_t *data)
{
    if (!fifo)
        return -1;
    
    if (!data)
        return -1;
    
    if (!fifo->f_p)
        return -1;
    
    if (fifo->f_num > 0) {
        (*data) = fifo->f_p[fifo->f_idxr];
        fifo->f_num--;
        
        if (fifo->f_idxr < (fifo->f_len - 1))
            fifo->f_idxr++;
        else
            fifo->f_idxr = 0;
    } else
        return -1;
    
    return 0;
}

int fifo_get_len(fifo_t *fifo)
{
    if (!fifo)
        return -1;
    
    return fifo->f_len;
}

int fifo_get_num(fifo_t *fifo)
{
    if (!fifo)
        return -1;
    
    return fifo->f_num;
}
