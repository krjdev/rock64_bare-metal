/**
 *
 * File Name: include/unistd.h
 * Title    : C Library
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

#ifndef ROCK64_UNISTD_H
#define ROCK64_UNISTD_H

#include <stdint.h>
#include <stddef.h>

#define STDIN_FILENO    0       /* Standard input */
#define STDOUT_FILENO   1       /* Standard output */
#define STDERR_FILENO   2       /* Standard error output */

extern ssize_t write(int fd, const void *buf, size_t len);
extern ssize_t read(int fd, void *buf, size_t len);
extern int close(int fd);
extern int fsync(int fd);

#endif
