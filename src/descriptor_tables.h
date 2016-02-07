#pragma once
#include <stdint.h>
#include "io.h"
#include "interrupt.h"
#include "printf.h"

//Structure of the GDT entry
//Bits:
//  0-15:   Segment Limit 0-15
//  16-31:  Base Address 0-15
//  32-39:  Base Address 16-23
//  40-43:  Type
//  44:     Descriptor type
//  45-46:  Ring level - ring 0-3
//  47:     Is segment present? 1=yes
//  48-51:  Limit 16-19
//  52:     Avaliable for system use
//  53:     Fucking nothing set to 0
//  54:     Operand size (0 = 16bit, 1 = 32bit)
//  55:     Granuality (0 = 1 byte, 1 = 1 Kilobyte)
//  56-63:  Bass Address 24-31
//So the granularity bye in this structure is also the limit_high that's missing

struct gdt_entry_struct{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
};
typedef struct gdt_entry_struct gdt_entry_t;

#define GDT_ENTRY(base, limit, access, granularity)\
    { (limit) & 0xFFFF,                                /* limit_low */ \
      (base) >> 0 & 0xFFFF,                            /* base_low */ \
      (base) >> 16 & 0xFF,                             /* base_middle */ \
      (access) & 0xFF,                                 /* access */ \
      ((limit) >> 16 & 0x0F) | ((granularity) & 0xF0), /* granularity */ \
      (base) >> 24 & 0xFF,                             /* base_high */ }

struct idt_entry_struct{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t zero;
    uint8_t type;
    uint16_t offset_high;
};
typedef struct idt_entry_struct idt_entry_t;

struct tss_entry_struct
{
   uint32_t prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
   uint32_t esp0;       // The stack pointer to load when we change to kernel mode.
   uint32_t ss0;        // The stack segment to load when we change to kernel mode.
   uint32_t esp1;       // Unused...
   uint32_t ss1;
   uint32_t esp2;
   uint32_t ss2;
   uint32_t cr3;
   uint32_t eip;
   uint32_t eflags;
   uint32_t eax;
   uint32_t ecx;
   uint32_t edx;
   uint32_t ebx;
   uint32_t esp;
   uint32_t ebp;
   uint32_t esi;
   uint32_t edi;
   uint32_t es;         // The value to load into ES when we change to kernel mode.
   uint32_t cs;         // The value to load into CS when we change to kernel mode.
   uint32_t ss;         // The value to load into SS when we change to kernel mode.
   uint32_t ds;         // The value to load into DS when we change to kernel mode.
   uint32_t fs;         // The value to load into FS when we change to kernel mode.
   uint32_t gs;         // The value to load into GS when we change to kernel mode.
   uint32_t ldt;        // Unused...
   uint16_t trap;
   uint16_t iomap;
} __attribute__((packed));
typedef struct tss_entry_struct tss_entry_t;
