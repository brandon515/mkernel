#pragma once 
#include <stdint.h>
#include "printf.h"

#define DIRECTORY_PRESENT (1<<0) 
#define DIRECTORY_READWRITE (1<<1) 
#define DIRECTORY_USER_ACCESS (1<<2) 
#define DIRECTORY_WRITE_THROUGH (1<<3)
#define DIRECTORY_CACHE_DISABLE (1<<4)
#define DIRECTORY_ACCESSED (1<<5)
#define DIRECTORY_SIZE_4MB (1<<7)
#define DIRECTORY_SIZE  1024

#define TABLE_PRESENT (1<<0)
#define TABLE_READWRITE (1<<1)
#define TABLE_SIZE 1024

typedef uint32_t page_directory_entry_t;
typedef uint32_t page_table_entry_t;


page_directory_entry_t page_directory[DIRECTORY_SIZE]__attribute__((aligned(4096)));
page_table_entry_t four_meg[TABLE_SIZE]__attribute__((aligned(4096)));

unsigned int init_page_directory();
page_directory_entry_t create_page_directory_entry(uintptr_t page_table_address, uint16_t flags);
page_table_entry_t create_page_table_entry(uintptr_t physical_memory_address, uint16_t flags);
