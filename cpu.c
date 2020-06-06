/**
 *
 * File Name: cpu.c
 * Title    : AArch64 CPU Functions
 * Project  : 
 * Author   : Copyright (C) 2020 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2020-06-06
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

#include <misc.h>

int cpu_get_cur_el(void)
{
    return (int) _cpu_get_el();
}

int cpu_get_cur_id(void)
{
    return (int) _cpu_get_id();
}
