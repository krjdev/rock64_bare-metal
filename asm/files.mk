# PINE64 ROCK64 Bare-Metal
#
# Assembler
# 
# asm

# Kernel
ASRC_KERN	+= asm/vector.S
ASRC_KERN	+= asm/start_kern.S
ASRC_KERN	+= asm/cache.S
ASRC_KERN	+= asm/self_kern.S
ASRC_KERN	+= asm/tlb.S
ASRC_KERN	+= asm/intr.S
ASRC_KERN	+= asm/syscall_kern.S

# User
ASRC_USER	+= asm/start_user.S
ASRC_USER	+= asm/self_user.S
ASRC_USER	+= asm/syscall_user.S
