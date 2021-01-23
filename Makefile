# PINE64 ROCK64 Bare-Metal

CROSS_COMPILE=aarch64-none-elf-

# Target Output
TARGET		= main.elf

RM		= rm -rf
CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld

ASFLAGS		+= -Wa,-mcpu=cortex-a53

CCFLAGS		+= -Wall
CCFLAGS		+= -Wextra
CCFLAGS		+= -ffreestanding
CCFLAGS		+= -ffunction-sections
CCFLAGS		+= -I ./include
CCFLAGS		+= -mcpu=cortex-a53

LDFLAGS		+= -nostdlib
LDFLAGS		+= --gc-sections
LDFLAGS		+= -Map=$(TARGET).map

# Linker Script
include ld/files.mk

# Architecture Sources
include asm/files.mk

# (Simple) Standard C Library Sources
include libc/files.mk

# Device Sources
include dev/files.mk

# Utility Sources
include util/files.mk

CSRC		+= init.c
CSRC		+= intr.c
CSRC		+= main.c

OBJ 		+= $(ASRC:.S=.o)
OBJ 		+= $(CSRC:.c=.o)

all: main

main: $(OBJ)
	@echo "[LD] $(TARGET)"
	@$(LD) -o $(TARGET) $(LDFLAGS) $(OBJ)

%.o: %.c
	@echo "[CC] $@"
	@$(CC) -c $(CCFLAGS) -o $@ $<

%.o: %.S
	@echo "[AS] $@"
	@$(CC) -c $(CCFLAGS) $(ASFLAGS) -o $@ $<

.PHONY: clean
clean:
	@echo "[CLEAN]"
	@$(RM) $(OBJ) $(TARGET) $(TARGET).map *~
