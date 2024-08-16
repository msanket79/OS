#ifndef __STRING_H_
#define __STRING_H_

#include<size_t.h>

extern size_t strlen ( const char* str );
extern char* strcpy(char* dest, const char* src);
extern void* memcpy(void *dest, const void* src, size_t count);
extern void* memset(void* dest, char val, size_t count);
extern unsigned short* memsetw(unsigned short* dest, unsigned short val, size_t count);


#endif