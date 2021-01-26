/**
 *
 * File Name: libc/heap.c
 * Title    : C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-16
 * Modified : 2021-01-26
 * Revised  : 
 * Version  : 0.1.1.0
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
    uint64_t *p_start;
    uint64_t *p_end;
    size_t len_bytes;
    size_t len_block;
    size_t free_bytes;
    size_t free_block;
};

static struct _heap heap;

static uint64_t *find_hole(size_t block_cnt)
{
    size_t block_len;
    size_t block_found;
    uint64_t *ptr;
    uint64_t *ptr_ret;
        
    ptr = heap.p_start;
    ptr_ret = ptr;
    block_len = 0;
    block_found = 0;
    
    do {
        if ((*ptr) == HEAP_MAGIC_BGN) {
            ptr++;
            block_len = (*ptr);
            ptr += (block_len + 2);
            
            if ((*ptr) == HEAP_MAGIC_END)
                block_found = 0;
            
            ptr++;
            ptr_ret = ptr;
        } else {
            block_found++;
            if (block_found >= (block_cnt + 4))
                return ptr_ret;
            
            ptr++;
        }
    } while (ptr < heap.p_end);
    
    return NULL;
}

static void *do_alloc(size_t block_cnt, size_t size)
{
    uint64_t *ptr;
    uint64_t *ptr_ret;
    
    if (!block_cnt)
        return NULL;
    
    if (!size)
        return NULL;
    
    ptr = find_hole(block_cnt);
    
    if (!ptr)
        return NULL;
    
    (*ptr) = HEAP_MAGIC_BGN;
    ptr++;
    (*ptr) = block_cnt;
    ptr++;
    (*ptr) = size;
    ptr++;
    ptr_ret = ptr;
    ptr += block_cnt;
    (*ptr) = HEAP_MAGIC_END;
    heap.free_block -= (block_cnt + 4);
    heap.free_bytes -= (heap.free_block * sizeof(uint64_t));
    return ptr_ret;
}

static void do_free(void *p)
{
    uint64_t *ptr;
    uint64_t *ptr_start;
    size_t block_cnt;
    
    if (!p)
        return;
    
    ptr = (uint64_t *) p;
    ptr -= 3;
    ptr_start = ptr;
    
    if ((*ptr) != HEAP_MAGIC_BGN)
        abort();
    
    ptr++;
    block_cnt = (*ptr);
    
    if (block_cnt == 0)
        abort();
    
    ptr += block_cnt + 2;
    
    if ((*ptr) != HEAP_MAGIC_END)
        abort();
    
    memset(ptr_start, 0, (block_cnt + 4) * sizeof(uint64_t));
    heap.free_block += (block_cnt + 4);
    heap.free_bytes += (heap.free_block * sizeof(uint64_t));
}

static size_t do_size(void *p)
{
    uint64_t *ptr;
    size_t block_cnt;
    size_t ret;
    
    if (!p)
        return 0;
    
    ptr = (uint64_t *) p;
    ptr -= 3;
    
    if ((*ptr) != HEAP_MAGIC_BGN)
        abort();
    
    ptr++;
    block_cnt = (*ptr);
    ptr++;
    ret = (*ptr);
    
    if (block_cnt == 0)
        abort();
    
    ptr += block_cnt + 1;
    
    if ((*ptr) != HEAP_MAGIC_END)
        abort();
    
    return ret;
}

void heap_init(void)
{
    heap.p_start = (uint64_t *) _self_user_get_heap_s();
    heap.p_end = (uint64_t *) _self_user_get_heap_e();
    heap.len_bytes = _self_user_get_heap_e() - _self_user_get_heap_s();
    heap.len_block = heap.len_bytes / sizeof(uint64_t);
    heap.free_bytes = heap.len_bytes;
    heap.free_block = heap.len_block;
}

void *heap_alloc(size_t size)
{
    size_t block_cnt;
    
    if (!size)
        return NULL;
    
    block_cnt = size / sizeof(uint64_t);
    
    if ((size % sizeof(uint64_t)) != 0)
        block_cnt++;
    
    return do_alloc(block_cnt, size);
}

void heap_free(void *ptr)
{
    if (!ptr)
        return;
    
    if (ptr < (void *) heap.p_start)
        return;
    
    if (ptr > (void *) heap.p_end)
        return;
    
    return do_free(ptr);
}

size_t heap_size(void *ptr)
{
    if (!ptr)
        return 0;
    
    if (ptr < (void *) heap.p_start)
        return 0;
    
    if (ptr > (void *) heap.p_end)
        return 0;
    
    return do_size(ptr);
}
