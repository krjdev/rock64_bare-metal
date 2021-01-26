# PINE64 ROCK64 Bare-Metal
#
# ld

LDFLAGS_KERN	+= -T ld/kern.ld
LDFLAGS_USER	+= -T ld/user.ld
LDFLAGS_MAIN	+= -T ld/main.ld
