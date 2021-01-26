# PINE64 ROCK64 Bare-Metal
#
# Kernel
# 
# kern

CSRC_KERN	+= kern/kern_init.c
CSRC_KERN	+= kern/kern_main.c
CSRC_KERN	+= kern/kern_intr.c
CSRC_KERN	+= kern/kern_dev.c
CSRC_KERN	+= kern/kern_sched.c
CSRC_KERN	+= kern/kern_syscall.c
CSRC_KERN	+= kern/kern_thread.c
CSRC_KERN	+= kern/kern_vfs.c
CSRC_KERN	+= kern/kern_vm.c
CSRC_KERN	+= kern/kern_panic.c
