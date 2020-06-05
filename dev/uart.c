/**
 *
 * File Name: dev/uart.c
 * Title    : RK3328 UART Driver
 * Project  : 
 * Author   : Copyright (C) 2020 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2020-06-05
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

#include <string.h>

#include <dev/io.h>

#define UART_BASE           0xFF130000
#define UART_RBR_OFFSET     0x0
#define UART_THR_OFFSET     0x0
#define UART_MCR_OFFSET     0x10
#define UART_LCS_OFFSET     0x14

void uart_init(void)
{
    
}

int uart_send(unsigned char *buf, int len)
{
    int i;
    unsigned int tmp;
    
    for (i = 0; i < len; i++) {
        io_wr08(UART_BASE + UART_THR_OFFSET, buf[i]);
        tmp = io_rd32(UART_BASE + UART_MCR_OFFSET);
        tmp |= (1 << 1);
        io_wr32(UART_BASE + UART_MCR_OFFSET, tmp);
        
        do {
            tmp = io_rd32(UART_BASE + UART_LCS_OFFSET);
        } while (!(tmp & 0x20));
    }
    
    return len;
}

int uart_recv(unsigned char *buf, int len)
{
    int i;
    int ret = 0;
    unsigned int tmp;
    
    tmp = io_rd32(UART_BASE + UART_LCS_OFFSET);
    
    if (!(tmp & 0x1))
        return 0;
    
    for (i = 0; i < len; i++) {
        buf[i] = io_rd08(UART_BASE + UART_THR_OFFSET);
        ret++;
        tmp = io_rd32(UART_BASE + UART_LCS_OFFSET);
    
        if (!(tmp & 0x1))
            return ret;
    }
    
    return ret;
}

void uart_putc(const char c)
{
    unsigned char buf[1];
    
    buf[0] = c;
    uart_send(buf, 1);
}

void uart_puts(const char *str)
{
    uart_send((unsigned char *) str, strlen(str));
}

int uart_getc(void)
{
    int ret;
    unsigned char buf[1];
    
    ret = uart_recv(buf, 1);
    
    if (ret)
        return (int) buf[0];
    else
        return -1;
}
