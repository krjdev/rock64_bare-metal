/**
 *
 * File Name: asm/syscall.S
 * Title    : AArch64 Syscalls for Userland
 * Project  : PINE64 ROCK64 Bare-Metal
 * Author   : Copyright (C) 2021 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2021-01-29
 * Modified : 2021-01-30
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
#include <asm/syscall.h>

.text

/* Process operations */
/* Exit normal */
SYSCALL(asm_SYS_proc_exit)
    mov x1, x0                  /* Exit code */
    mov x0, #__SYS_PROC_EXIT
    svc #__SYS_PROC

/* Exit abnormal */
SYSCALL(asm_SYS_proc_abort)
    mov x0, #__SYS_PROC_ABRT
    svc #__SYS_PROC

/* File operations */
/* Close file */
SYSCALL(asm_SYS_file_close)
    mov x1, x0                  /* File descriptor */
    mov x0, #__SYS_FILE_CLOS
    svc #__SYS_FILE

/* Write to file */
SYSCALL(asm_SYS_file_write)
    mov x3, x2                  /* Length */
    mov x2, x1                  /* Pointer to Buffer */
    mov x1, x0                  /* File descriptor */
    mov x0, #__SYS_FILE_WRIT
    svc #__SYS_FILE

/* Read from file */
SYSCALL(asm_SYS_file_read)
    mov x3, x2                  /* Length */
    mov x2, x1                  /* Pointer to Buffer */
    mov x1, x0                  /* File descriptor */
    mov x0, #__SYS_FILE_READ
    svc #__SYS_FILE

/* Synchronize file (flush buffers) */
SYSCALL(asm_SYS_file_fsync)
    mov x1, x0                  /* File descriptor */
    mov x0, #__SYS_FILE_SYNC
    svc #__SYS_FILE

.end
