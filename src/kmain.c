#include "kmain.h"

uint32_t kinit(){
    fb_clear_monitor();
    uint32_t ret = init_page_directory();
    if(ret != 0){
        return ret;
    }
    enable_paging((uintptr_t)&page_directory);
    return 0;
}

uint32_t kmain(){
    uint32_t ret = kinit();
    if(ret != 0){
        return ret;
    }
    register_print();
    /*printf(SERIAL,   "signed integer: %d\nthe character: %c\nscientific notation: %e\nnow with a capital E: %E\nFloating number: %f\nOctal number: %o\nString: %s\nUnsigned integer: %u\nHex Number: %x\nNow with capitals: %X\nPointer: %p\n",
                    -12231, 't', 21344423.0, 21344423.0, 123.4567, 024234, "\"this is a test!\"", 23412, 0xdeadbeef, 0xDEADBEEF, (void*)&test_ptr);
    printf(SERIAL, "# of chars in this line: %n", &test_ptr);
    printf(SERIAL, "%d\n", test_ptr);
    printf(SERIAL, "printing percentage sign %%\n");*/
    return 0;
}
