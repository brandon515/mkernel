#include "kstring.h"

size_t strlen(const char *buf){
    size_t len = 0;
    while(buf[len] != '\0'){
        len++;
    }
    return len;
}
