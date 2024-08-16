#include<idt.h>
#include<string.h>
#include<hal.h>
#include<debugDisplay.h>


struct idtr{
    uint16_t limit;

    // base of the idt
    uint32_t base;
} __attribute__((packed));

 struct idt_descriptor _idt[MAX_INTERRUPTS];

 struct idtr _idtr;

static void idtInstall();

 void i86DefaultHandler();

// this will load the idtr register
void idtInstall(){  
    
    __asm__("lidt %0"::"m" (_idtr) :);

}
uint32_t interrupt_number;
// this is the default handler which will be called for all the interrupts which are not defined
 void i86DefaultHandler(){
    
    __asm__ volatile (
    "mov %%eax, %[result]"  // Move the value of `eax` into the memory location
    : [result] "=m" (interrupt_number)  // Output operand, memory location of `interrupt_number`
    :  // No input operands
    : "eax"  // Clobbered register
);
    debugClrScr(0x18);
    debugGoToXY(0,0);
    debugSetColor(0x1e);
    debugPrintf("i86 default handler : Unhandled exception %x",interrupt_number);
    for(;;);
}

struct idt_descriptor* getIdtDescriptor(uint32_t i){
       if(i>MAX_INTERRUPTS) return (void*)0;

       return &_idt[i];
}
int setIdtDescriptor(uint32_t i,uint16_t flags,uint16_t segment,I86InterruptHandler irq){
    // desc out of range
    if(i>MAX_INTERRUPTS) return 0;

    // not a valid handler
    if(!irq) return 0;
    
    // extract the address of the request handler
    uint64_t base=(uint64_t)&(*irq);


    // set the offset in the selector 
    _idt[i].offsetLo=(uint16_t)(base & 0xffff);
    _idt[i].offsetHi=(uint16_t)((base>>16) & 0xffff);

    // this byte is reserved and is set to zero
    _idt[i].reserved=0;

    _idt[i].segment=segment;


    _idt[i].flags=(uint8_t)flags;


    return 0;
}

int IdtInitialize(uint16_t codeSel){
    uint32_t i=0;
    // prepare the idtr and fill the space of idtr with 0
    _idtr.limit=sizeof(struct idt_descriptor)*MAX_INTERRUPTS-1;
    _idtr.base=(uint32_t)&_idt[0];
    memset((void*)(&_idt[0]),0,sizeof(struct idt_descriptor)*MAX_INTERRUPTS-1);
    
    // if a interrupt n is called and there is no handler for n then GPR will occur and will interrupt int 13 and if there is no handler
    // defined for 13 then double fault int 8 will ocur and if there is no handler then triple fault occurs
    for(i=0;i<MAX_INTERRUPTS;i++){
        if(i==14) continue;
        setIdtDescriptor(i, I86_DESC_BIT32 | I86_DESC_PRESENT,codeSel,(I86InterruptHandler)i86DefaultHandler);

    }

    // now install the idt using igdt instruction
    idtInstall();

    return 0;
}

 void idtprint(int y){
    static struct idtr _idtr_store;
__asm__ ("sidt %0":"=m" (_idtr_store)::"memory");
    // debugClrScr(0x18);
    debugGoToXY(4,y);
    debugSetColor (0x70);
    debugPrintf("%x---%x",_idtr_store.base,_idtr_store.limit);
    debugPrintf("   --%x---",_idt);

}