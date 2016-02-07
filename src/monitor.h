#pragma once
#include "io.h"
#include <stdint.h>
#include <stddef.h>
// Command port recieves a special code describing the data coming in
#define FB_COMMAND_PORT     0x3D4
#define FB_DATA_PORT        0x3D5

#define CURSOR_HIGH_BYTE    0x0E
#define CURSOR_LOW_BYTE     0x0F
#define SCREEN_WIDTH        80
#define SCREEN_HEIGHT       25
#define TAB_LENGTH          8 

int32_t fb_clear_monitor();
int32_t fb_write_cell(uint32_t i, uint16_t character);
int32_t fb_set_cursor(uint16_t i);
void fb_start_cursor();
int32_t kprint(uint8_t *buf, uint32_t len);
int32_t fb_write_array(uint8_t *buf, uint8_t color, uint16_t len, uint16_t cursor);
uint16_t fb_get_character(uint8_t letter, uint8_t color);
