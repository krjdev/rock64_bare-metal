/**
 *
 * File Name: libc/stdlib/exit.c
 * Title    : C Library
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-30
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

#include <syscall.h>

void exit(int code)
{
    /* TODO: Flush buffers of opened files
     * 
     * Currently not implemented in internal stream functions
     */
    SYS_proc_exit(code);
}
