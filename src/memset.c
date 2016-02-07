#include "memset.h"

void *memset(void *s, int c, size_t n){
    unsigned char byte = (unsigned char)c;
    unsigned char *target = (unsigned char*)s;
    for(uint32_t i = 0; i < n; i++){
        target[i] = byte;
    }
    return (void*)target;
}
