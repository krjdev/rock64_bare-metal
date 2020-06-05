/**
 *
 * File Name: stack.S
 * Title    : AArch64 Stack
 * Project  : 
 * Author   : Copyright (C) 2020 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2020-06-03
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

#define KERN_STACK_SIZE     4096

.section .stack ,"aw",%nobits
.space KERN_STACK_SIZE
.text
