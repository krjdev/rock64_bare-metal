# PINE64 ROCK64 Bare-Metal
# 
# Makefile

ifeq ($(CROSS_COMPILE),)
CROSS_COMPILE=aarch64-none-elf-
endif

# Target Output
TARGET		= main.elf
TARGET_KERN	= kern.elf
TARGET_USER	= user.elf

RM		= rm -rf
CP		= cp -Rf
CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
OBJCOPY		= $(CROSS_COMPILE)objcopy

ASFLAGS		+= -Wa,-mcpu=cortex-a53
ASFLAGS		+= -D_ASM_ASSEMBLER_

CCFLAGS		+= -Wall
CCFLAGS		+= -Wextra
CCFLAGS		+= -ffreestanding
CCFLAGS		+= -ffunction-sections
CCFLAGS		+= -mcpu=cortex-a53

# Kernel
CCFLAGS_KERN	= $(CCFLAGS)
CCFLAGS_KERN	+= -I ./sys/include

# Userland libc (Internal)
CCFLAGS_USER	= $(CCFLAGS)
CCFLAGS_USER	+= -I ./libc/include

# Userland
CCFLAGS_USER	+= -I ./include

# Global GNU ld flags
LDFLAGS		+= -nostdlib

# Kernel
LDFLAGS_KERN	= $(LDFLAGS)
LDFLAGS_KERN	+= --gc-sections
LDFLAGS_KERN	+= -Map=$(TARGET_KERN).map

# Userland
LDFLAGS_USER	= $(LDFLAGS)
LDFLAGS_USER	+= --gc-sections
LDFLAGS_USER	+= -Map=$(TARGET_USER).map

# Kernel
LDFLAGS_MAIN	= $(LDFLAGS)
LDFLAGS_MAIN	+= -Map=$(TARGET).map

# Kernel
#include sys/files.mk

# Userland
include files.mk

#AOBJ_KERN 	+= $(ASRC_KERN:.S=.o)
#COBJ_KERN 	+= $(CSRC_KERN:.c=.o)

AOBJ_USER 	+= $(ASRC_USER:.S=.o)
COBJ_USER 	+= $(CSRC_USER:.c=.o)

all: user

#main: kern user
#	@echo "[LD] $(TARGET)"
#	@$(OBJCOPY) -O elf64-littleaarch64 -S $(TARGET_USER) $(TARGET_USER) 2> /dev/null
#	@$(LD) -o $(TARGET) $(LDFLAGS_MAIN) $(TARGET_KERN) $(TARGET_USER)

# Kernel
#kern: $(AOBJ_KERN) $(COBJ_KERN)
#	@echo "[LD] $(TARGET_KERN)"
#	@$(LD) -o $(TARGET_KERN) $(LDFLAGS_KERN) $(AOBJ_KERN) $(COBJ_KERN)

#$(COBJ_KERN): %.o: %.c
#	@echo "[CC] $@"
#	@$(CC) -c $(CCFLAGS_KERN) -o $@ $<

#$(AOBJ_KERN): %.o: %.S
#	@echo "[AS] $@"
#	@$(CC) -c $(CCFLAGS_KERN) $(ASFLAGS) -o $@ $<

# Userland
user: $(AOBJ_USER) $(COBJ_USER)
	@echo "[LD] $(TARGET_USER)"
	@$(LD) -o $(TARGET_USER) $(LDFLAGS_USER) $(AOBJ_USER) $(COBJ_USER)
	
$(COBJ_USER): %.o: %.c
	@echo "[CC] $@"
	@$(CC) -c $(CCFLAGS_USER) -o $@ $<

$(AOBJ_USER): %.o: %.S
	@echo "[AS] $@"
	@$(CC) -c $(CCFLAGS_USER) $(ASFLAGS) -o $@ $<

.PHONY: clean
clean:
	@echo "[CLEAN]"
#	@$(RM) $(AOBJ_KERN) $(COBJ_KERN)
#	@$(RM) $(TARGET_KERN) $(TARGET_KERN).map
	@$(RM) $(AOBJ_USER) $(COBJ_USER)
	@$(RM) $(TARGET_USER) $(TARGET_USER).map
	@$(RM) $(TARGET) $(TARGET).map
