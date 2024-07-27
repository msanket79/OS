#include<string.h>



size_t str_len(const char*str){
    size_t len=0;
    while(str[len++]);
    return len;
}