/**
 *
 * File Name: dev/io.c
 * Title    : RK3328 (Memory) I/O
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

#ifndef DEV_IO_H
#define DEV_IO_H

extern void io_wr32(unsigned int addr, unsigned int val);
extern void io_wr16(unsigned int addr, unsigned short val);
extern void io_wr08(unsigned int addr, unsigned char val);
extern unsigned int io_rd32(unsigned int addr);
extern unsigned short io_rd16(unsigned int addr);
extern unsigned char io_rd08(unsigned int addr);

#endif
