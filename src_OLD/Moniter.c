#include "Moniter.h"

uint8_t getColor(vgaColor fg, vgaColor bg)
{
	return fg | bg<<4;
}

void putChar(char c, uint8_t color, Cursor *cursor)
{
	uint16_t *mem = (uint16_t*)0xb8000;
	if(c == '\n' || c == '\r')
	{
		cursor->x = 0;
		cursor->y++;
	}
	else if(c == '\t')
	{
		cursor->x += 4-cursor->x%4;
	}
	else
	{
		mem[cursor->y*80+cursor->x] = c | color<<8;
		cursor->x += 1;
	}
	if(cursor->x >= 80)
	{
		cursor->x = 0;
		cursor->y++;
	}
	uint16_t cursorLoc = cursor->y*80+cursor->x;
	outb(0x3D4, 14);
	outb(0x3D5, cursorLoc>>8);
	outb(0x3D4, 15);
	outb(0x3D5, cursorLoc);
}

void writeString(char* string, uint8_t color, Cursor *cursor)
{
	uint16_t i = 0;
	while(string[i] != '\0')
	{
		putChar(string[i], color, cursor);
		i++;
	}
}

void moniterClear(uint8_t color)
{
	uint16_t *screen = (uint16_t*)0xb8000;
	uint16_t screensize = 80*25;
	for(int i = 0; i < screensize; i++)
	{
		screen[i] = ' ' | color<<8;
	}
}
