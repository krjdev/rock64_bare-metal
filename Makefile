CROSS_COMPILE=aarch64-none-elf-

RM 	= rm -rf
CC 	= $(CROSS_COMPILE)gcc
LD	= $(CROSS_COMPILE)ld

TARGET 	= hello.elf
CCFLAGS = -Wall -I ./include -ffreestanding -mcpu=cortex-a53
LDFLAGS = -nostdlib -T hello.lds

ASRC	+= misc.S
ASRC	+= stack.S
ASRC	+= start.S

OBJ 	+= $(ASRC:.S=.o)

CSRC	+= dev/cru.c
CSRC	+= dev/io.c
CSRC	+= dev/uart.c

CSRC	+= lib/memcpy.c
CSRC	+= lib/memset.c
CSRC	+= lib/strlen.c

CSRC	+= cpu.c
CSRC	+= main.c

OBJ 	+= $(CSRC:.c=.o)

all: main

main: $(OBJ)
	$(LD) -o $(TARGET) $(LDFLAGS) $(OBJ)

%.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

%.o: %.S
	$(CC) -c $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJ) *~
