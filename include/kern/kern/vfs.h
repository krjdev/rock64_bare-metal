/**
 *
 * File Name: include/kern/kern/vfs.h
 * Title    : Kernel
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

#ifndef ROCK64_KERN_KERN_VFS_H
#define ROCK64_KERN_KERN_VFS_H

#include <stdint.h>

#define VFS_FD_STDIN        0
#define VFS_FD_STDOUT       1
#define VFS_FD_STDERR       2

extern int kern_vfs_init(void);
extern int kern_vfs_write(int fd, const uint8_t *buf, int len);
extern int kern_vfs_read(int fd, uint8_t *buf, int len);

#endif
