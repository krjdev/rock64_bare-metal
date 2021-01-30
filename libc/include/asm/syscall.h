/**
 *
 * File Name: libc/include/asm/syscall.h
 * Title    : C Library - Internal
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

#ifndef ROCK64_LIBC_ASM_SYSCALL_H
#define ROCK64_LIBC_ASM_SYSCALL_H

/* Process operations */
#define __SYS_PROC                  0   /* Process operation */

#define __SYS_PROC_EXIT             0   /* Exit normal */
#define __SYS_PROC_ABRT             1   /* Exit abnormal */
#define __SYS_PROC_ALLO             2   /* Allocate memory */
#define __SYS_PROC_DEAL             3   /* Deallocate memory */

/* Filesystem operations */
#define __SYS_FILE                  1   /* File operation */

#define __SYS_FILE_OPEN             0   /* Open file -- Currently not implemted */
#define __SYS_FILE_CLOS             1   /* Close file */
#define __SYS_FILE_WRIT             2   /* Wrtie to file */
#define __SYS_FILE_READ             3   /* Read from file */
#define __SYS_FILE_SYNC             4   /* Synchronize file */

#ifndef _ASM_ASSEMBLER_

#include <stdint.h>
#include <stddef.h>

/* Process operations */
/* Exit normal */
extern void asm_SYS_proc_exit(int code);

/* Exit abnormal */
extern void asm_SYS_proc_abort(void);

/* Allocate memory */
extern void *asm_SYS_proc_alloc(size_t len, int flags);

/* Deallocate (free) memory */
extern int *asm_SYS_proc_dealloc(const void *buf);

/* File operations */
/* Close file */
extern int asm_SYS_file_close(int fd);

/* Write to file */
extern ssize_t asm_SYS_file_write(int fd, const void *buf, size_t len);

/* Read from file */
extern ssize_t asm_SYS_file_read(int fd, void *buf, size_t len);

/* Synchronize file (flush buffers) */
extern int asm_SYS_file_fsync(int fd);

#endif
#endif
