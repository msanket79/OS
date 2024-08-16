// ;=================================================
// ;        Headers
// ;=================================================

#include<gdt.h>
#include<string.h>
#include<stdint.h>
#include<_null.h>
#include<debugDisplay.h>
// this setups a GDT descriptor in GDT at index i
// extern void gdtSetDescriptor(uint32_t i,uint64_t base ,uint64_t limit,uint8_t access,uint8_t grand);

// // returns the desc at i
// extern gdt_descriptor* gdtGetDescriptor(int i);

// // initialies gdt
// extern int gdtInitialize();

// ;=================================================
// ;			Implementation private structurs
// ;=================================================
// pointer to GDT
struct gdtr{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


// ;=================================================
// ;		Implementation private data
// ;=================================================

// global descriptor table
static struct gdt_descriptor _gdt[MAX_DESCRIPTORS];

// pointer to the gdt
static struct gdtr _gdtr;


// ;=================================================
// ;		Implementation private functions
// ;=================================================

static void gdtInstall();

void gdtInstall(){
    __asm__ volatile("lgdt %0" : :"m" (_gdtr):"memory");
}


void gdtSetDescriptor(uint32_t i,uint64_t base,uint64_t limit ,uint8_t access, uint8_t grand){
    if(i>MAX_DESCRIPTORS){
        return;
    }
    memset ((void*)&_gdt[i], 0, sizeof (struct gdt_descriptor));
    _gdt[i].limit=(uint16_t)(limit);
    _gdt[i].baseLo=(uint16_t)(base);
    _gdt[i].baseMid=(uint8_t)(base>>16);
    _gdt[i].baseHi=(uint8_t)(base>>24);

    _gdt[i].access=(uint8_t)(access);
    _gdt[i].grand=(uint8_t)( (limit>>16) & 0x0f );
    _gdt[i].grand|=grand & 0xf0;
} 

struct gdt_descriptor* gdtGetDescriptor(uint32_t i){
    if(i>MAX_DESCRIPTORS) return NULL;
    return &_gdt[i];
}

int gdtInitialize(){
    _gdtr.limit=(sizeof(struct gdt_descriptor)*MAX_DESCRIPTORS-1);
    _gdtr.base=(uint32_t)&_gdt[0];

// setting the null gdt descriptor
    gdtSetDescriptor(0,0,0,0,0);
// setting the kernel code desc
    gdtSetDescriptor(1,0,0xffffffff,
    I86_GDT_DESC_READWRITE | I86_GDT_DESC_IS_CODE | I86_GDT_DESC_CODEDATA |I86_GDT_DESC_IN_MEM,
    I86_GDT_GRAND_LIMITHI_MASK | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_4K
    );

// setting the kernel data desc
    gdtSetDescriptor(2,0,0xffffffff,
    I86_GDT_DESC_READWRITE | I86_GDT_DESC_CODEDATA | I86_GDT_DESC_IN_MEM,
    I86_GDT_GRAND_LIMITHI_MASK | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_4K
    );

    gdtInstall();
    return 0;
}


void gdtprint(int y){
    static struct gdtr _gdtr_store;
__asm__ ("sgdt %0":"=m" (_gdtr_store)::"memory");
    // debugClrScr(0x18);
    debugGoToXY(4,y);
    debugSetColor (0x70);
    debugPrintf("%x---%x",_gdtr_store.base,_gdtr_store.limit);
    debugPrintf("%x--",_gdt);
}