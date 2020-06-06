/**
 *
 * File Name: misc.S
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

#include <asm.h>

.text

FUNCTION(_cpu_get_el)
    mrs x0, CurrentEL
    and x0, x0, #0xC
    asr x0, x0, #2
    ret

FUNCTION(_cpu_get_id)
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    ret

.end
