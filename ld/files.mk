# PINE64 ROCK64 Bare-Metal
#
# Userland
# 
# ld

# Userland Linker Script
LDFLAGS_USER	+= -T ld/user.ld

# Global Linker Script
LDFLAGS_MAIN	+= -T ld/main.ld
