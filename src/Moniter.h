#ifndef MONITER_H_INCLUDED
#define MONITER_H_INCLUDED
#include "common.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum _vgaColor{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
} vgaColor;

typedef struct _Cursor{
	uint16_t x;
	uint16_t y;
} Cursor;

uint8_t getColor(vgaColor fg, vgaColor bg);
void putChar(char c, uint8_t color, Cursor* cursor);
void writeString(char* string, uint8_t color, Cursor* cursor);
void moniterClear(uint8_t color);

#endif