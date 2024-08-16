#ifndef _GDT_H_
#define _GDT_H_

#include<stdint.h>


// defines
#define MAX_DESCRIPTORS 3 //max amount of desc in gdt


// ;=================================================
// ;		    ACCESS BITS			
// ;=================================================
#define I86_GDT_DESC_ACCESS 0X0001
//desc is readable and writtable deafault: read only
#define I86_GDT_DESC_READWRITE 0X0002

// set expansion direction
#define I86_GDT_DESC_EXPANSION 0X0004

// desc is code segemnt  default: data segment
#define I86_GDT_DESC_IS_CODE 0X0008

// desc is code or data type deafult :system defined desc
#define I86_GDT_DESC_CODEDATA 0X0010

// desc is ring 3  default: ring level 0
#define I86_GDT_DESC_PREV_LEVEL 0X0060

//set "in memory bit"
#define I86_GDT_DESC_IN_MEM 0X0080

// ;=================================================
// ;			GRANULARITY BIT
// ;=================================================

// masks out limithi 4bits of limit
#define I86_GDT_GRAND_LIMITHI_MASK 0X0F

// Set the os bit 
#define I86_GDT_GRAND_OS 0X10

// set 32bit bit desc default:16bit
#define I86_GDT_GRAND_32BIT 0X40

// limit multiplied by 4k default:none
#define I86_GDT_GRAND_4K 0X80



// A single gdt entry
struct gdt_descriptor{
    // 0-15 bits of segment limit
    uint16_t limit;

    // 0 -23 bits of base address
    uint16_t baseLo;
    uint8_t baseMid;

    // access flags
    uint8_t access;
    uint8_t grand;

    // bits 24-32 of base addrs
    uint8_t baseHi;
} __attribute__((packed));

// this setups a GDT descriptor in GDT at index i
extern void gdtSetDescriptor(uint32_t i,uint64_t base ,uint64_t limit,uint8_t access,uint8_t grand);

// returns the desc at i
extern struct gdt_descriptor* gdtGetDescriptor(uint32_t i);

// initialies gdt
extern int gdtInitialize();

extern void gdtprint(int y);










#endif