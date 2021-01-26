/**
 *
 * File Name: include/kern/dev/mmio.h
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

#ifndef ROCK64_KERN_DEV_MMIO_H
#define ROCK64_KERN_DEV_MMIO_H

#include <stdint.h>

extern void mmio_wr32(uint64_t addr, uint32_t val);
extern void mmio_wr16(uint64_t addr, uint16_t val);
extern void mmio_wr08(uint64_t addr, uint8_t val);
extern uint32_t mmio_rd32(uint64_t addr);
extern uint16_t mmio_rd16(uint64_t addr);
extern uint8_t mmio_rd08(uint64_t addr);

#endif
