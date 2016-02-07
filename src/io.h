#pragma once
#include <stdint.h>
#include <stddef.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void gdt_flush(uint32_t);
void idt_flush(uint32_t);
void register_print();
uint32_t get_kernel_stack();
void tss_flush(uint32_t);
void enable_paging(uint32_t);
