/**
 *
 * File Name: main.c
 * Title    : Kernel Main
 * Project  : 
 * Author   : Copyright (C) 2020 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2020-06-05
 * Modified : 2020-06-06
 * Revised  : 
 * Version  : 0.1.1.0
 * License  : ISC (see LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <cpu.h>
#include <dev/cru.h>
#include <dev/uart.h>

void kern_main(void)
{
    int c;
    
    uart_init();
    uart_puts("Pine64 Rock64\r\n");
    uart_puts("Running on ");
    
    switch (cpu_get_cur_id()) {
    case 0:
        uart_puts("CPU0 ");
        break;
    case 1:
        uart_puts("CPU1 ");
        break;
    case 2:
        uart_puts("CPU2 ");
        break;
    case 3:
        uart_puts("CPU3 ");
        break;
    default:
        uart_puts("CPU? ");
    }
    
    switch (cpu_get_cur_el()) {
    case 0:
        uart_puts("EL0\r\n");
        break;
    case 1:
        uart_puts("EL1\r\n");
        break;
    case 2:
        uart_puts("EL2\r\n");
        break;
    case 3:
        uart_puts("EL3\r\n");
        break;
    default:
        uart_puts("EL?\r\n");
    }
    
    uart_puts("Press 'r' to reset the board!\r\n");
    
    do {
        c = uart_getc();
    } while (c != 'r');
    
    uart_puts("Resetting...\r\n");
    cru_reset();
    
    while (1)
        ;
}
