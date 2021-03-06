/**
 *
 * File Name: dev/mmio.c
 * Title    : Memory-Mapped I/O
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

#include <dev/mmio.h>

void mmio_wr32(uint64_t addr, uint32_t val)
{
    uint32_t *ptr;
    
    ptr = (uint32_t *) addr;
    (*ptr) = val;
}

void mmio_wr16(uint64_t addr, uint16_t val)
{
    uint16_t *ptr;
    
    ptr = (uint16_t *) addr;
    (*ptr) = val;
}

void mmio_wr08(uint64_t addr, uint8_t val)
{
    uint8_t *ptr;
    
    ptr = (uint8_t *) addr;
    (*ptr) = val;
}

uint32_t mmio_rd32(uint64_t addr)
{
    uint32_t *ptr;
    
    ptr = (uint32_t *) addr;
    return (*ptr);
}

uint16_t mmio_rd16(uint64_t addr)
{
    uint16_t *ptr;
    
    ptr = (uint16_t *) addr;
    return (*ptr);
}

uint8_t mmio_rd08(uint64_t addr)
{
    uint8_t *ptr;
    
    ptr = (uint8_t *) addr;
    return (*ptr);
}
