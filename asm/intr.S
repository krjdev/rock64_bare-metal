/**
 *
 * File Name: asm/intr.S
 * Title    : AArch64 Kernel
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-25
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

#include <asm/asm.h>

.text

FUNCTION(_cpu_intr_enable)
    msr DAIFclr, #7
    ret

FUNCTION(_cpu_intr_disable)
    msr DAIFset, #7
    ret

.end
