# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=boot.asm kernel.c common.c Moniter.c
OBJ=$(patsubst %.c,obj/%.o,$(filter %.c, $(SOURCES)))
OBJ+=$(patsubst %.asm,obj/%.o,$(filter %.asm, $(SOURCES)))

CFLAGS=-c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib -T link.ld -lgcc
ASFLAGS=-felf

all: $(SOURCES) link
	$()

clean:
	-rm obj/*.o bin/kernel

link:
	i686-elf-gcc $(LDFLAGS) -o bin/kernel $(OBJ)

%.c: $(@:%.c=.h)
	i686-elf-gcc $(CFLAGS) src/$@ -o obj/$(@:%.c=%.o)

%.asm:
	nasm $(ASFLAGS) src/$@ -o obj/$(@:%.asm=%.o)

run: bin/kernel
	qemu-system-i386 -kernel bin/kernel