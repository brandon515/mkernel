#include "memcpy.h"

void *memcpy(void *dest, const void *src, size_t n){
    uint8_t *srcint = (uint8_t*)src;
    uint8_t *destint = (uint8_t*)dest;

    for(uint32_t i = 0; i < n; i++){
        destint[i] = srcint[i];
    }
    return (void*)destint;
}
