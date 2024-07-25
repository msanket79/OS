
;*******************************************************
;
;	Stage3.asm
;		A basic 32 bit binary kernel running
;
;	OS Development Series
;*******************************************************

org	0x100000			; Kernel starts at 1 MB

bits	32				; 32 bit code

jmp	Stage3				; jump to entry point

%include "include/stdio.inc"

msg db  0x0A, 0x0A, "                       - Falcon OS -"
    db  0x0A, 0x0A, "                     MOS 32 Bit Kernel Executing", 0x0A, 0

Stage3:

	;-------------------------------;
	;   Set registers		;
	;-------------------------------;

	mov	ax, 0x10		; set data segments to data selector (0x10)
	mov	ds, ax
	mov	ss, ax
	mov	es, ax
	mov	esp, 90000h		; stack begins from 90000h

	;---------------------------------------;
	;   Clear screen and print success	;
	;---------------------------------------;

	call	ClrScr32
	mov	ebx, msg
	call	PutS32

	;---------------------------------------;
	;   Stop execution			;
	;---------------------------------------;

	cli
	hlt



