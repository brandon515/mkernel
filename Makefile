# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=kernel.c boot.asm common.c
OBJ=$(patsubst %.c,obj/%.o,$(filter %.c, $(SOURCES)))
OBJ+=$(patsubst %.asm,obj/%.o,$(filter %.asm, $(SOURCES)))

CFLAGS=-m32 -c -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-m elf_i386 -T link.ld
ASFLAGS=-f elf32

all: $(SOURCES) link
	$()

clean:
	-rm obj/*.o bin/kernel

link:
	ld $(LDFLAGS) -o bin/kernel $(OBJ)

%.c: $(@:%.c=.h)
	gcc $(CFLAGS) src/$@ -o obj/$(@:%.c=%.o)

%.asm:
	nasm $(ASFLAGS) src/$@ -o obj/$(@:%.asm=%.o)

run: bin/kernel
	qemu-system-i386 -kernel bin/kernel