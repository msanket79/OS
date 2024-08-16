#ifndef _IDT_H_
#define _IDT_H_

#include<stdint.h>

#define MAX_INTERRUPTS 256

// it is of type 0D110 
#define I86_DESC_BIT16 0x06 //00110
#define I86_DESC_BIT32 0x0E //01110

// the ring level of the desc
#define I86_DESC_RING1 0x40
#define I86_DESC_RING2 0x20
#define I86_DESC_RING3 0x60

// if there is desc for that interrupt or not
#define I86_DESC_PRESENT 0x80

// the interrupt implemenation uses different stack based on the interrupt number so we just pass the function pointer
// and let the handler decide which stack to use
typedef void ( *I86InterruptHandler)(void);

struct idt_descriptor{
    uint16_t offsetLo;
    uint16_t segment;
    uint8_t reserved;
    uint8_t flags;
    uint16_t offsetHi
} __attribute__((packed));

extern struct idt_descriptor* getIdtDescriptor(uint32_t i);

extern int setIdtDescriptor(uint32_t i,uint16_t flags,uint16_t segment,I86InterruptHandler );

extern int IdtInitialize(uint16_t codeSel);

extern void idtprint(int y);
#endif
