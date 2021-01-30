# PINE64 ROCK64 Bare-Metal
#
# Userland C Library Sources
# 
# libc

CSRC_USER	+= libc/init.c
CSRC_USER	+= libc/heap.c
CSRC_USER	+= libc/stream.c
CSRC_USER	+= libc/syscall.c
CSRC_USER	+= libc/exit.c

# Userland C Library ctype Functions
include libc/ctype/files.mk

# Userland C Library stdio Functions
include libc/stdio/files.mk

# Userland C Library stdlib Functions
include libc/stdlib/files.mk

# Userland C Library string Functions
include libc/string/files.mk

# Userland C Library unistd Functions
include libc/unistd/files.mk
