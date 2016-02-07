#pragma once
#include <stdint.h>
#include <stddef.h>
#include "printf.h"

struct interrupt_state{
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t int_no;
    uint32_t err_code;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
};
typedef struct interrupt_state interrupt_state_t;

void isr_handler(interrupt_state_t params);
