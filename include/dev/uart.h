/**
 *
 * File Name: dev/uart.h
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

#ifndef DEV_UART_H
#define DEV_UART_H

extern void uart_init(void);
extern int uart_send(unsigned char *buf, int len);
extern int uart_recv(unsigned char *buf, int len);
extern void uart_putc(const char c);
extern void uart_puts(const char *str);
extern int uart_getc(void);

#endif
