/**
 *
 * File Name: kern/kern_vfs.c
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

#include <errno.h>

#include <kern/dev.h>
#include <kern/vfs.h>

int kern_vfs_init(void)
{
    return ESUCCESS;
}

int kern_vfs_write(int fd, const uint8_t *buf, int len)
{
    if (fd != VFS_FD_STDOUT)
        return ENODIR;
    
    return kern_dev_write_class(DEV_CLASS_STDOUT, buf, len);
}

int kern_vfs_read(int fd, uint8_t *buf, int len)
{
    return ESUCCESS;
}
