# PINE64 ROCK64 Bare-Metal
#
# Userland
# 
# 

# Userland Linker Scripts
include ld/files.mk

# Userland Assembly Sources
include asm/files.mk

# Userland C Library Sources
include libc/files.mk

# Userland Sources
CSRC_USER	+= main.c
