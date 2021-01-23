/**
 *
 * File Name: libc/stdlib/heap.c
 * Title    : Simple Standard C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-16
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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <asm/self.h>

#define HEAP_MAGIC_BGN      0x4283428338243824
#define HEAP_MAGIC_END      0x3824382442834283

struct _heap {
    uint64_t *start;
    uint64_t *end;
    uint64_t size;
    uint64_t free;
};

static struct _heap heap;

static uint64_t *find_hole(unsigned int size)
{
    int i;
    int block_cnt;
    uint64_t *p;
    uint64_t *p_ret;
    uint64_t len;
    
    block_cnt = heap.size / (sizeof(uint64_t));
    p = heap.start;
    
    for (i = 0; i < block_cnt; i++) {
        if ((*p) == HEAP_MAGIC_BGN) {
            p += sizeof(uint64_t);
            i++;
            p += (*p);
            i += ((*p) / sizeof(uint64_t));
            
            if ((*p) != HEAP_MAGIC_END)
                abort();
            
            p += sizeof(uint64_t);
            i++;
            len = 0;
        } else {
            p_ret = p;
            
            while ((*p) != HEAP_MAGIC_BGN) {
                p += sizeof(uint64_t);
                i++;
                len += sizeof(uint64_t);
            }
            
            if (size <= len)
                return p_ret;
        }
    }
    
    return NULL;
}

static void *do_alloc(unsigned int size)
{
    uint64_t *ptr;
    uint64_t *ptr_ret;
    
    if (size < 1)
        return NULL;
    
    ptr = find_hole(size);
    
    if (!ptr)
        return NULL;
    
    (*ptr) = HEAP_MAGIC_BGN;
    ptr += sizeof(uint64_t);
    (*ptr) = size;
    ptr += sizeof(uint64_t);
    ptr_ret = ptr;
    ptr += size;
    (*ptr) = HEAP_MAGIC_END;
    heap.free -= (size + (3 * sizeof(uint64_t)));
    return ptr_ret;
}

static void do_free(void *ptr)
{
    uint64_t *p;
    uint64_t *p_data;
    uint64_t len;
    
    if (!ptr)
        return;
    
    p_data = (uint64_t *) ptr;
    p = (p_data - (2 * sizeof(uint64_t)));
    
    if ((*p) != HEAP_MAGIC_BGN)
        return;
    
    p += sizeof(uint64_t);
    len = (*p);
    
    if (len == 0)
        return;
    
    if ((len % sizeof(uint64_t)) != 0)
        len += (len % sizeof(uint64_t));
    
    p += len;
    
    if ((*p) != HEAP_MAGIC_END)
        return;
    
    p = (p_data - (2 * sizeof(uint64_t)));
    heap.free += (len + (3 * sizeof(uint64_t)));
    memset(p, 0, len + (3 * sizeof(uint64_t)));
}

static uint64_t do_size(void *ptr)
{
    uint64_t *p;
    uint64_t *p_data;
    uint64_t len;
    
    if (!ptr)
        return 0;
    
    p_data = (uint64_t *) ptr;
    p = (p_data - (2 * sizeof(uint64_t)));
    
    if ((*p) != HEAP_MAGIC_BGN)
        return 0;
    
    p += sizeof(uint64_t);
    len = (*p);
    
    if (len == 0)
        return 0;
    
    if ((len % sizeof(uint64_t)) != 0)
        len += (len % sizeof(uint64_t));
    
    p += len;
    
    if ((*p) != HEAP_MAGIC_END)
        return 0;
    
    return len;
}

void heap_init(void)
{
    heap.start = (uint64_t *) _self_get_heap_s();
    heap.end = (uint64_t *) _self_get_heap_e();
    heap.size = _self_get_heap_e() - _self_get_heap_s();
    heap.free = heap.size - (3 * sizeof(uint64_t));
}

void *heap_alloc(unsigned int size)
{
    if (size < 1)
        return NULL;
    
    if ((size + (3 * sizeof(uint64_t))) > heap.free)
        return NULL;
    
    if ((size % sizeof(uint64_t)) != 0)
        return do_alloc(size + (size % sizeof(uint64_t)));
    else
        return do_alloc(size);
}

void heap_free(void *ptr)
{
    if (!ptr)
        return;
    
    if (ptr < (void *) heap.start)
        return;
    
    if (ptr > (void *) (heap.end - sizeof(uint64_t)))
        return;
    
    return do_free(ptr);
}

int heap_size(void *ptr)
{
    if (!ptr)
        return -1;
    
    if (ptr < (void *) heap.start)
        return -1;
    
    if (ptr > (void *) (heap.end - sizeof(uint64_t)))
        return -1;
    
    return do_size(ptr);
}
