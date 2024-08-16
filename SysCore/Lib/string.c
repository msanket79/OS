#include<string.h>

size_t strlen(const char*str){
    size_t len=0;
    while(str[len++]);
    return len;
}

// copies null terminated string from src to dest
char* strcpy(char *dest,const char*src){
    char *dest_s=dest;
    while(*dest++=*src++);
    return dest_s;
}

void *memcpy(void* dest, const void* src, size_t count){
    const char * sp=(const char*)src;
    char * dp=(char *)dest;
    while(count){
        *dp++=*sp++;
        count--;
    }
    return dest;
}
void *memset(void *dest, char val, size_t count){
    unsigned char *dp=(unsigned char *) dest;
    while(count){
        *dp=val;
        dp++;
        count--;
    }

    return dest;
}

unsigned short* memsetw(unsigned short* dest, unsigned short val, size_t count){
    unsigned short*dp=dest;
    while(count){
        *dp=val;
        dp++;
        count--;
    }
    return dest;
}



