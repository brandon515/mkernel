.macro ISR_NOERRCODE i  # define a macro, taking one parameter
  .global isr\i        # %1 accesses the first parameter.
  .type isr\i, @function
  isr\i:
    cli
    pushl $0 #"error" code
    pushl $\i
    jmp isr_common_stub
  .size isr\i, .-isr\i
.endm

.macro ISR_ERRCODE i
  .global isr\i
  .type isr\i, @function
  isr\i:
    cli
    #error code pushed by cpu
    pushl $\i
    jmp isr_common_stub
  .size isr\i, .-isr\i
.endm

.macro IRQ i
  .global isr\i
  .type isr\i, @function
  isr\i:
    cli
    pushl $0 #"error" code
    pushl $(\i+32)
    jmp isr_common_stub
  .size isr\i, .-isr\i
.endm

.extern isr_handler

.type isr_common_stub, @function
isr_common_stub:
    pushl %eax
    pushl %ecx
    pushl %edx
    pushl %ebx
    pushl %ebp
    pushl %esi
    pushl %edi
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    movl $0x10 /* Kernel Data Segment */, %ebp
    movl %ebp, %ds
    movl %ebp, %es
    movl %ebp, %fs
    movl %ebp, %gs

    movl %cr2, %ebp
    pushl %ebp

    movl %esp, %ebx
    subl $4, %esp
    andl $0xFFFFFFF0, %esp /* 16-byte align stack */
    movl %ebx, (%esp)
    call isr_handler
    movl %ebx, %esp

    popl %ebp
    movl %ebp, %cr2

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popl %edi
    popl %esi
    popl %ebp
    popl %ebx
    popl %edx
    popl %ecx
    popl %eax

    addl $8, %esp
    iret
.size isr_common_stub, .-isr_common_stub

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_ERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 32
