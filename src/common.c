#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

typedef unsigned int uint32;

void putc(char *arr, char c, uint32 x, uint32 y)
{
	arr[(y * 80 + x) * 2] = c;
}

#endif