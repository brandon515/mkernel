global loader

MAGIC_NUMBER        equ 0x1BADB002
FLAGS               equ 0x0
CHECKSUM            equ 0-(MAGIC_NUMBER+FLAGS)

section .text:
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader: 
    mov eax, 0xCAFEBABE
    mov esp, 0xDEADBEEF
.loop:
    jmp .loop

KERNEL_STACK_SIZE   equ 4096

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE
