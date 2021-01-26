/**
 *
 * File Name: dev/gic.c
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

#include <errno.h>
#include <stdint.h>

#include <dev/mmio.h>

#define GIC400_BASE             0xFF810000

#define GICD_CTRL               0x1000
#define GICD_TYPER              0x1004
#define GICD_IIDR               0x1008
#define GICD_IGROUPRn           0x1080
#define GICD_ISENABLERn         0x1100
#define GICD_ICENABLERn         0x1180
#define GICD_ISPENDRn           0x1200
#define GICD_ICPENDRn           0x1280
#define GICD_ISACTIVERn         0x1300
#define GICD_ICACTIVERn         0x1380
#define GICD_IPRIORITYn         0x1400
#define GICD_ITARGETRn          0x1800
#define GICD_ICFGRn             0x1C00
#define GICD_PPISR              0x1D00
#define GICD_SPISRn             0x1D04
#define GICD_SGIR               0x1F00
#define GICD_CPENDSGIRn         0x1F10
#define GICD_SPENDSGIRn         0x1F20
#define GICD_PIDR4              0x1FD0
#define GICD_PIDR5              0x1FD4
#define GICD_PIDR6              0x1FD8
#define GICD_PIDR7              0x1FDC
#define GICD_PIDR0              0x1FE0
#define GICD_PIDR1              0x1FE4
#define GICD_PIDR2              0x1FE8
#define GICD_PIDR3              0x1FEC
#define GICD_CIDR0              0x1FF0
#define GICD_CIDR1              0x1FF4
#define GICD_CIDR2              0x1FF8
#define GICD_CIDR3              0x1FFC

#define GICC_CTRL               0x2000
#define GICC_PMR                0x2004
#define GICC_BPR                0x2008
#define GICC_IAR                0x200C
#define GICC_EOIR               0x2010
#define GICC_RPR                0x2014
#define GICC_HPPIR              0x2018
#define GICC_ABPR               0x201C
#define GICC_AIAR               0x2020
#define GICC_AEOIR              0x2024
#define GICC_AHPPIR             0x2028
#define GICC_APR0               0x20D0
#define GICC_NSAPR0             0x20E0
#define GICC_IIDR               0x20FC
#define GICC_DIR                0x3000

struct _gic {
    int irq_nr;
    int cpu_nr;
    int security;
    int lspi;
};

static struct _gic gic;

void gic_intr_enable(int irq_nr)
{
    uint32_t tmp;
    int offset;
    int position;
    
    if (gic.irq_nr <= irq_nr)
        return;
    
    offset = ((irq_nr / 32) * 4);
    position = irq_nr % 32;
    tmp = mmio_rd32(GIC400_BASE + GICD_ISENABLERn + offset);
    tmp |= (1 << position);
    mmio_wr32(GIC400_BASE + GICD_ISENABLERn + offset, tmp);
}

void gic_intr_set_prior(int irq_nr, uint8_t prior)
{
    uint32_t tmp;
    int offset;
    int position;
    
    if (gic.irq_nr <= irq_nr)
        return;
    
    offset = ((irq_nr / 4) * 4);
    position = irq_nr % 4;
    tmp = mmio_rd32(GIC400_BASE + GICD_IPRIORITYn + offset);
    tmp &= ~(0xFF << position);
    tmp |= (prior << position);
    mmio_wr32(GIC400_BASE + GICD_IPRIORITYn + offset, tmp);
}

void gic_intr_set_group(int irq_nr, int group)
{
    uint32_t tmp;
    int offset;
    int position;
    
    if (gic.irq_nr <= irq_nr)
        return;
    
    offset = ((irq_nr / 32) * 4);
    position = irq_nr % 32;
    tmp = mmio_rd32(GIC400_BASE + GICD_IGROUPRn + offset);
    
    if (group)
        tmp |= (1 << position);
    else
        tmp &= ~(1 << position);
    
    mmio_wr32(GIC400_BASE + GICD_IGROUPRn + offset, tmp);
}

void gic_intr_clear(int irq_nr)
{
    if (gic.irq_nr <= irq_nr)
        return;
}

int gic_init(void)
{
    uint32_t tmp;
    
    tmp = mmio_rd32(GIC400_BASE + GICD_TYPER);
    gic.irq_nr = ((tmp & 0x1F) + 1) * 32;
    gic.cpu_nr = ((tmp & 0xE0) >> 5) + 1;
    
    if (tmp & 0x400)
        gic.security = 1;
    else
        gic.security = 0;
    
    gic.lspi = (tmp & 0xF800) >> 11;
    
    mmio_wr32(GIC400_BASE + GICD_CTRL, 0x3);
    mmio_wr32(GIC400_BASE + GICC_CTRL, 0x3);
    mmio_wr32(GIC400_BASE + GICC_PMR, 0x0);
    return ESUCCESS;
}
