# PINE64 ROCK64 Bare-Metal
#
# C Library
# 
# libc

include libc/ctype/files.mk
include libc/stdio/files.mk
include libc/stdlib/files.mk
include libc/string/files.mk
include libc/unistd/files.mk

CSRC_USER	+= libc/init.c
CSRC_USER	+= libc/heap.c
CSRC_USER	+= libc/syscall.c
