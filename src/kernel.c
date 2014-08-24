
/* Check if the compiler thinks if we are targeting the wrong operating system. */
#include "kernel.h"
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kmain(void)
{
	char *str = "my first kernel";

	Cursor cur;
	cur.x = 20;
	cur.y = 0;
	uint8_t color = getColor(COLOR_WHITE, COLOR_RED);

	moniterClear(color);
	writeString(str, color, &cur);
	
	return;
}
