#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
    /* TODO: Is there any reason to force the use of eax and edx? */
}
void *memset(void *str, int c, size_t n);
void *memmove(void *str1, const void *str2, size_t n);
void *memcpy(void *str1, const void *str2, size_t n);
int memcmp(const void *str1, const void *str2, size_t n);

#endif