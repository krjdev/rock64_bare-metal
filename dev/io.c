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

void io_wr32(unsigned long addr, unsigned int val)
{
    unsigned int *ptr;
    
    ptr = (unsigned int *) addr;
    (*ptr) = val;
}

void io_wr16(unsigned long addr, unsigned short val)
{
    unsigned short *ptr;
    
    ptr = (unsigned short *) addr;
    (*ptr) = val;
}

void io_wr08(unsigned long addr, unsigned char val)
{
    unsigned char *ptr;
    
    ptr = (unsigned char *) addr;
    (*ptr) = val;
}

unsigned int io_rd32(unsigned long addr)
{
    unsigned int *ptr;
    
    ptr = (unsigned int *) addr;
    return (*ptr);
}

unsigned short io_rd16(unsigned long addr)
{
    unsigned short *ptr;
    
    ptr = (unsigned short *) addr;
    return (*ptr);
}

unsigned char io_rd08(unsigned long addr)
{
    unsigned char *ptr;
    
    ptr = (unsigned char *) addr;
    return (*ptr);
}
