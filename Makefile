CROSSCCOM=/home/theman515/opt/cross/bin/i686-elf-gcc
CROSSACOM=/home/theman515/opt/cross/bin/i686-elf-as
SOURCES=loader.asm io.asm monitor.c kmain.c kstring.c serial.c interrupt_handler.c descriptor_tables.c interrupt.asm printf.c memset.c memmove.c memcmp.c memcpy.c print_registers_c.c paging.c
OBJ=$(patsubst %.c,obj/%.o,$(filter %.c, $(SOURCES)))
OBJ+=$(patsubst %.asm,obj/%.o,$(filter %.asm, $(SOURCES)))

CFLAGS=-c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib -T link.ld -lgcc
ASFLAGS=

all: $(SOURCES) link copy generate
	$()

copy:
	cp -rf bin/kernel.elf iso/boot

generate:
	    genisoimage -R                              \
					-b boot/grub/stage2_eltorito    \
					-no-emul-boot                   \
					-boot-load-size 4               \
					-A MyOs                         \
					-input-charset utf8             \
					-quiet                          \
					-boot-info-table                \
					-o bin/MyOs.iso                 \
					iso
clean:
	rm obj/*.o bin/*

link:
	$(CROSSCCOM) $(LDFLAGS) -o bin/kernel.elf $(OBJ) 

%.c: $(@:%.c=.h)
	$(CROSSCCOM) $(CFLAGS) src/$@ -o obj/$(@:%.c=%.o)

%.asm:
	$(CROSSACOM) $(ASFLAGS) src/$@ -o obj/$(@:%.asm=%.o)

run:
	qemu-system-x86_64 -d int,cpu_reset -monitor stdio -serial file:serial.out -cdrom bin/MyOs.iso
