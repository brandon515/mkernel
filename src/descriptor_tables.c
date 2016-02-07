#include "descriptor_tables.h"
#define GRAN_64_BIT_MODE    (1 << 5)
#define GRAN_32_BIT_MODE    (1 << 6)
#define GRAN_4KIB_BLOCKS    (1 << 7)
#define GRAN_SEGMENTS_MODE (GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS)

tss_entry_t tss ={
    .ss0    = 0x10,
    .esp0   = 0,
    .es     = 0x10,
    .cs     = 0x08,
    .ds     = 0x13,
    .fs     = 0x13,
    .gs     = 0x13,
};

gdt_entry_t gdt[]={
    GDT_ENTRY(0,0,0,0),                                 //Null Segment
    GDT_ENTRY(0, 0xFFFFFFFF, 0x9A, GRAN_SEGMENTS_MODE), //Kernel Code   - 0x08
    GDT_ENTRY(0, 0xFFFFFFFF, 0x92, GRAN_SEGMENTS_MODE), //Kernel Data   - 0x10
    GDT_ENTRY(0, 0xFFFFFFFF, 0xFA, GRAN_SEGMENTS_MODE), //User Code     - 0x18
    GDT_ENTRY(0, 0xFFFFFFFF, 0xf2, GRAN_SEGMENTS_MODE), //User Data     - 0x20
    GDT_ENTRY(0, sizeof(tss) - 1, 0xE9, 0x00),
};

uint16_t gdt_size_minus_one = sizeof(gdt)-1;
