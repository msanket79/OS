#ifndef _CPU_H_
#define _CPU_H_
#include<stdint.h>

// this will setup the idt,gdt and will start the cpu
extern int i86CpuInit();

// this will be used to close the cpu and shutdown the system
extern void i86CpuShutdown();

#endif