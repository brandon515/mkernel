.global outb
.global inb
.global gdt_flush
.global idt_flush
.global register_print
.global get_kernel_stack
.global tss_flush
.global enter_protected_mode
.global enable_paging

#stack: [esp + 8]   data being pushed
#       [esp + 4]   port to push the data
#       [esp]       return address
outb:
    mov 8(%esp), %al
    mov 4(%esp), %dx
    outb %al, %dx
    ret

#stack: [esp + 4]   port to read
inb:
    mov 4(%esp), %dx
    inb  %dx, %al
    ret

#stack: 4(esp)   pointer to gdt_entry_t struct
gdt_flush:
    mov 4(%esp), %eax
    lgdt (%eax)
    ret
/*    mov 0x10, %ax
    #mov %ax, %ds
    #mov %ax, %es
    #mov %ax, %fs
    #mov %ax, %gs
    #mov %ax, %ss
    #mov 0x10, %cs
    ljmpl $(1*8), $(flush)
flush:
    ret
*/

#stack: 4(esp)  pointer to idt_entry_t struct

#stack: 4(esp)   pointer to idt_entry_t struct
idt_flush:
    mov 4(%esp), %eax
    lidt (%eax)
    ret

#returns the top of the kernel stack
get_kernel_stack:
    mov stack_top, %eax
    ret

#stack: 2(esp)  word with the segment in the GDT that contains the TSS
tss_flush:
    mov 2(%esp), %ax
    ltr %ax
    ret
    

.extern print_registers_c
register_print:
    pusha
    call print_registers_c
    popa
    ret
#stack: 4(%esp) long with pointer to page directory
enable_paging:
    movl 4(%esp), %eax
    movl %eax, %cr3
    movl %cr0, %eax
    or $0x80000000, %eax
    movl %eax, %cr0
