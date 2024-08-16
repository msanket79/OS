#ifndef _HAL_H_
#define _HAL_H_

#include<stdint.h>

extern int halInitialize();
extern int halShutdown();
extern void getInterrupt(uint32_t n);


#endif
