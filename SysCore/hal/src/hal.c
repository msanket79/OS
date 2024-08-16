#include<hal.h>
#include<cpu.h>



int halInitialize(){
    i86CpuInit();
    return 0;
}

int halShutdown(){
    i86CpuShutdown();
    return 0;
}




