#include "paging.h"


unsigned int init_page_directory(){
    for(unsigned int i = 0; i < DIRECTORY_SIZE; i++){
        page_directory[i] = 0; 
    }
    //place the page_directory in the final entry to translate addresses easier
    page_directory_entry_t address_to_directory = create_page_directory_entry((uintptr_t)&page_directory, DIRECTORY_PRESENT | DIRECTORY_READWRITE);
    if(address_to_directory == 0){
        return 1;
    }
    page_directory[DIRECTORY_SIZE-1] = address_to_directory;
    //1:1 map the first 4 mb (basically the kernel and bios) to avoid headaches
    for(unsigned int i = 0; i < TABLE_SIZE; i++){
        page_table_entry_t entry = create_page_table_entry(i*1024*4, TABLE_PRESENT | TABLE_READWRITE);
        if(entry == 0){
            return 2;
        }
        four_meg[i] = entry;
    }
    page_directory_entry_t four_meg_entry = create_page_directory_entry((uintptr_t)&four_meg, DIRECTORY_PRESENT | DIRECTORY_READWRITE);
    if(four_meg_entry == 0){
        return 3;
    }
    page_directory[0] = four_meg_entry;
    return 0;
}

page_directory_entry_t create_page_directory_entry(uintptr_t page_table_address, uint16_t flags){
    page_directory_entry_t ret = page_table_address & 0xFFFFF000;
    uintptr_t zero = page_table_address & 0xFFF;
    //return 0 if the page_table_address is not 4k aligned
    if(zero != 0){
        return 0;
    }
    ret = ret | flags;
    return ret;
}

page_table_entry_t create_page_table_entry(uintptr_t physical_memory_address, uint16_t flags){
    return create_page_directory_entry(physical_memory_address, flags);
}

void map_page_table(page_directory_entry_t entry){
    unsigned int free_page_index = 0;
    for(free_page_index = 0; free_page_index < DIRECTORY_SIZE-1; free_page_index++){
        if((page_directory[free_page_index] & 1) == 0){
            break;
        }
    }
    page_directory[free_page_index] = entry;
}
