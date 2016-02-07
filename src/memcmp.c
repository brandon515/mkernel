#include "memcmp.h"

int memcmp(const void *s1, const void *s2, size_t n){
    uint8_t *s1int = (uint8_t*)s1;
    uint8_t *s2int = (uint8_t*)s2;
    for(uint32_t i = 0; i < n; i++){
        if(s1int[i] != s2int[i]){
            return s1int[i]-s2int[i];
        }
    }
    return 0;
}
