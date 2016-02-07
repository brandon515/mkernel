#include "print_registers_c.h"

void print_registers_c(uint32_t EDI,uint32_t ESI,uint32_t EBP,uint32_t ESP,uint32_t EBX,uint32_t EDX,uint32_t ECX,uint32_t EAX){
    printf(STDIO, "REGISTERS\nEAX: %X8\tECX: %X8\nEDX: %X8\tEBX: %X8\nESP: %X8\tEBP: %X8\nESI: %X8\tEDI: %X8\n", EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI);
}
