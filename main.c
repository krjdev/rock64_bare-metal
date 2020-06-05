/**
 *
 * File Name: main.c
 * Title    : Kernel Main
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

#include <dev/cru.h>
#include <dev/uart.h>

void kern_main(void)
{
    int c;
    
    uart_init();
    uart_puts("Pine64 Rock64\r\n");
    uart_puts("Press 'r' to reset the board!\r\n");
    
    do {
        c = uart_getc();
    } while (c != 'r');
    
    uart_puts("Resetting...\r\n");
    cru_reset();
    
    while (1)
        ;
}
