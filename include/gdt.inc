%ifndef __GDT_INC_FALCONOS_7999_INCLUDED_
%define __GDT_INC_FALCONOS_7999_INCLUDED_

; 16bit me hai abhi
bits 16

;=================================================
;				Install gdt
;=================================================
InstallGDT:
    cli
    pusha
    lgdt [toc]
    sti
    popa
    
    ret


; isme gdt install karunga sabse phle gdt banate hai
gdt_start:
     
; NULL descritor offset (0x0) Each entry is 8bytes remember  ;sabse phla hai null descriptor
    dd 0
    dd 0

; Kernel Code segment (0x8)

    dw 0FFFFh ; bhai yeh segment ki limit
    dw 0;  ; yeh base ke chhote 16bits
    db 0; yeh base ke middle 8bits
    db 10011010b
    db 11001111b
    db 0; higher bits of base

; kernel Data segment (0x10)
    ;ab banaunga datasegment- sab same rkh bss usme data descriptor karde
    dw 0FFFFh
    dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0

;User space code (0x18)

    dw 0FFFFh
    dw 0
    db 0
    db 11111010b ; just chnaged the ring level to 3
    db 11001111b
    db 0

;User space data (0x20)

    dw 0FFFFh
    dw 0
    db 0
    db 11110010b ; just chnaged the ring level to 3
    db 11001111b
    db 0

gdt_end:
toc: ;pointer to the gdt
    dw gdt_end - gdt_start - 1; ;size -1 of gdt
    dd gdt_start ;base of gdt

%define NULL_DESC 0
%define CODE_DESC 0x8
%define DATA_DESC 0x10


%endif; __GDT_INC_FALCONOS_7999_INCLUDED_