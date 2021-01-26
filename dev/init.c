/**
 *
 * File Name: dev/init.c
 * Title    : Devices
 * Project  : PINE64 ROCK64 Bare-Metal
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

#include <dev/rk_cru.h>
#include <dev/rk_timer.h>
#include <dev/rk_uart.h>

int dev_init(void)
{
    int ret;
    
    ret = rk_cru_init();
    
    if (ret != ESUCCESS)
        return ret;
    
    ret = rk_timer_init();
    
    if (ret != ESUCCESS)
        return ret;
    
    ret = rk_uart_init();
    
    if (ret != ESUCCESS)
        return ret;
    
    return ESUCCESS;
}
