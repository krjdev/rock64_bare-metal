/**
 *
 * File Name: dev/rk_cru.c
 * Title    : Rockchip RK3328 Clock and Reset Controller
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

#include <errno.h>
#include <stdint.h>

#include <dev/mmio.h>

#define RK_CRU_BASE                     0xFF440000
#define RK_CRU_GLB_SRST_FST             0x9C
#define RK_CRU_GLB_SRST_FST_MAGIC       0xFDB9

int rk_cru_init(void)
{
    return ESUCCESS;
}

void rk_cru_reset(void)
{
    uint64_t addr;
    
    addr = RK_CRU_BASE + RK_CRU_GLB_SRST_FST;
    mmio_wr32(addr, RK_CRU_GLB_SRST_FST_MAGIC);
}
