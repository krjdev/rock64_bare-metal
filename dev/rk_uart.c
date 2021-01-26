/**
 *
 * File Name: dev/rk_uart.c
 * Title    : Rockchip RK3328 UART
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
#include <stdlib.h>

#include <dev/mmio.h>

#include <kern/dev.h>

#define UART0_BASE          0xFF110000 /* Not used */
#define UART1_BASE          0xFF120000 /* Not used */
#define UART2_BASE          0xFF130000
#define UARTX_RBR           0x0
#define UARTX_THR           0x0
#define UARTX_MCR           0x10
#define UARTX_LCS           0x14

#define UART0_IRQ           87 /* Not used */
#define UART1_IRQ           88 /* Not used */
#define UART2_IRQ           89

struct _rk_uart {
    uint64_t base;
};

int rk_uart_send(dev_t *dev, const uint8_t *buf, int len)
{
    int i;
    uint32_t tmp;
    struct _rk_uart *rk_uart = NULL;
    
    if (!dev)
        return ENODEV;
    
    if (!buf)
        return EINVAL;
    
    if (len < 1)
        return EINVAL;
    
    rk_uart = kern_dev_config(dev);
    
    if (!rk_uart)
        return ENODEV;
    
    for (i = 0; i < len; i++) {
        mmio_wr08(rk_uart->base + UARTX_THR, buf[i]);
        tmp = mmio_rd32(rk_uart->base + UARTX_MCR);
        tmp |= (1 << 1);
        mmio_wr32(rk_uart->base + UARTX_MCR, tmp);
        
        do {
            tmp = mmio_rd32(rk_uart->base + UARTX_LCS);
        } while (!(tmp & 0x20));
    }
    
    return len;
}

int rk_uart_recv(dev_t *dev, uint8_t *buf, int len)
{
    int i;
    int ret;
    uint32_t tmp;
    struct _rk_uart *rk_uart = NULL;
    
    if (!dev)
        return ENODEV;
    
    if (!buf)
        return EINVAL;
    
    if (len < 1)
        return EINVAL;
    
    rk_uart = kern_dev_config(dev);
    
    if (!rk_uart)
        return ENODEV;
    
    tmp = mmio_rd32(rk_uart->base + UARTX_LCS);
    
    if (!(tmp & 0x1))
        return 0;
    
    for (i = 0; i < len; i++) {
        buf[i] = mmio_rd08(rk_uart->base + UARTX_THR);
        ret++;
        tmp = mmio_rd32(rk_uart->base + UARTX_LCS);
    
        if (!(tmp & 0x1))
            return ret;
    }
    
    return ret;
}

int rk_uart_init(void)
{
    int ret;
    dev_t *dev = NULL;
    struct _rk_uart *rk_uart = NULL;
    
    rk_uart = (struct _rk_uart *) malloc(sizeof(struct _rk_uart));
    
    if (!rk_uart)
        return ENODEV;
    
    dev = kern_dev_create(DEV_CLASS_STDOUT | DEV_CLASS_STDIN, 
                          DEV_TYPE_CHAR, 0, (void *) rk_uart);
    
    if (!dev) {
        free(rk_uart);
        return ENODEV;
    }
    
    rk_uart->base = UART2_BASE;
    ret = kern_dev_op_write(dev, &rk_uart_send);
    
    if (ret != ESUCCESS) {
        free(rk_uart);
        kern_dev_free(dev);
        return ENODEV;
    }
    
    kern_dev_op_read(dev, &rk_uart_recv);
    
    if (ret != ESUCCESS) {
        free(rk_uart);
        kern_dev_free(dev);
        return ENODEV;
    }
    
    return ESUCCESS;
}
