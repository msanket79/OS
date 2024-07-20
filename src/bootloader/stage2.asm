;=================================================
;			Stage 2
;=================================================

bits 16					; we are still in real mode

org 0x500				; we are loaded above bios


jmp main				; jump to main

%include "./src/bootloader/stdio.inc"
%include "./src/bootloader/gdt.inc"
%include "./src/bootloader/a20.inc"

;=================================================
;				Data section
;=================================================

Msg	db	"Preparing to load Falcon OS...",13,10,0


;=================================================
;				Stage 2 entry
;=================================================

main:
	;Set segments and stack

	cli 
	xor ax,ax
	mov ds,ax
	mov es,ax
	mov ax,0x9000
	mov ss,ax
	mov sp,0xFFFF
	sti
	;printing the message
	mov si,Msg
	call Puts16

	;=================================================
	;			Install GDT
	;=================================================
	call InstallGDT

	;=================================================
	;			Enable A20
	;=================================================
	call EnableA20KeyboardOutputPort
	;=================================================
	;			Go into Protected mode
	;=================================================
	
	cli;
	mov eax,cr0
	or eax,1
	mov cr0,eax

	jmp CODE_DESC:stage3 ; far jump to set the CS to 08h


;=================================================
;		Stage 3
;=================================================

bits 32

stage3:
	;now set the data segments to data desc
	mov ax,DATA_DESC ; 16bytes from gdt base
	mov ds,ax
	mov ss,ax
	mov es,ax
	mov esp,90000h ; stack begins from 90000h

;=================================================
;		STOP here
;=================================================
	cli
	hlt
