
MACHINE := $(shell uname -m)

ifeq ($(MACHINE), x86_64)
	FORMAT=elf64
else
	FORMAT=elf
endif

all:
	nasm -f $(FORMAT) wpc.asm 
	ld wpc.o -o wpc
	 