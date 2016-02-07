#include "memmove.h"

void *memmove(void *dest, const void *src, size_t n){
    uint8_t temp[n];
    uint8_t *srcint = (uint8_t*)src;
    uint8_t *destint = (uint8_t*)dest;

    memcpy(&temp, srcint, n);
    memcpy(destint, &temp, n);
    
    return (void*)destint;
}
