# PINE64 ROCK64 Bare-Metal
#
# Kernel Library
# 
# libkern

include libkern/ctype/files.mk
include libkern/stdlib/files.mk
include libkern/stdio/files.mk
include libkern/string/files.mk

CSRC_KERN	+= libkern/init.c
CSRC_KERN	+= libkern/heap.c
CSRC_KERN	+= libkern/fifo.c
