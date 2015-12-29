CROSSCOM=/home/theman515/opt/cross/bin/i686-elf-gcc
SOURCES=loader.asm
OBJ=$(patsubst %.c,obj/%.o,$(filter %.c, $(SOURCES)))
OBJ+=$(patsubst %.asm,obj/%.o,$(filter %.asm, $(SOURCES)))

CFLAGS=-c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib -T link.ld -lgcc
ASFLAGS=-felf

all: $(SOURCES) link copy generate
	$()

copy:
	mv bin/kernel.elf iso/boot

generate:
	    genisoimage -R                              \
					-b boot/grub/stage2_eltorito    \
					-no-emul-boot                   \
					-boot-load-size 4               \
					-A MyOs                         \
					-input-charset utf8             \
					-quiet                          \
					-boot-info-table                \
					-o MyOs.iso                     \
					iso
clean:
	-rm obj/*.o bin/kernel

link:
	$(CROSSCOM) $(LDFLAGS) -o bin/kernel.elf $(OBJ)

%.c: $(@:%.c=.h)
	$(CROSSCOM) $(CFLAGS) src/$@ -o obj/$(@:%.c=%.o)

%.asm:
	nasm $(ASFLAGS) src/$@ -o obj/$(@:%.asm=%.o)

run: bin/kernel
	bochs -f bochsrc.txt -q
