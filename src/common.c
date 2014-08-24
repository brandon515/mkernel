#include "common.h"

void *memset(void *str, int c, size_t n)
{
	int *strPtr = (int*)str;
	for(unsigned int i = 0; i < n; i++)
	{
		strPtr[i] = c;
	}
	return str;
}
void *memmove(void *str1, const void *str2, size_t n)
{
	void *buffer = (void*)0xFFFFFFFF-n;
	memcpy(buffer, str2, n);
	memcpy(str1, buffer, n);
	return str1;
}

void *memcpy(void *str1, const void *str2, size_t n)
{
	char *arr1 = (char*)str1;
	const char *arr2 = (const char*)str2;
	for(uint32_t i = 0; i < n; i++)
	{
		arr1[i] = arr2[i];
	}
	return str1;
}

int memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char *arr1 = (unsigned char*)str1, *arr2 = (unsigned char*)str2;
	for(uint32_t i = 0; i < n; i++)
	{
		if(arr1[i] != arr2[i])
		{
			return arr1[i]-arr2[i];
		}
	}
	return 0;
}
