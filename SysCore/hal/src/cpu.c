#include<cpu.h>
#include<gdt.h>
#include<idt.h>



// this will be used to close the cpu and shutdown the system


int i86CpuInit(){
    
    // init the gdt
    gdtInitialize();
    // init the idt
    IdtInitialize(0x8);
    return 0;
}


// shutdown the cpu 

void i86CpuShutdown(){
    
}