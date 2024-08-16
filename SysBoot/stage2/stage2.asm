;=================================================
;			Stage 2
;=================================================

bits 16					; we are still in real mode

org 0x500				; we are loaded above bios


jmp main				; jump to main

%include "stdio.inc"
%include "gdt.inc"
%include "a20.inc"
%include "fat12.inc"
%include "common.inc"


;=================================================
;				Data section
;=================================================

loadingMsg	db	"Searching for OS...",13,10,0
msgFailure db  "***Fatal*** missing or currupt OS Press any Key to reboot",0x0D,0x0A,0x0A,0x00



;=================================================
;				Stage 2 entry
;=================================================

main:
	;Set segments and stack

	cli 
	xor ax,ax
	mov ds,ax
	mov es,ax
	mov ax,0x0
	mov ss,ax
	mov sp,0xFFFF
	sti


	;=================================================
	;			Install GDT
	;=================================================
	call InstallGDT

	;=================================================
	;			Enable A20
	;=================================================
	call EnableA20KeyboardOutputPort

	;=================================================
	;			Print loading message
	;=================================================
	;printing the message
	mov si,loadingMsg
	call Puts16

	;=================================================
	;			Init the File system
	;=================================================

	call LoadRoot

	;=================================================
	;		Load Kernel
	;=================================================
	mov ebx,0	;BX:BP buffer to load to
	mov bp,IMAGE_RMODE_BASE ;load kernel at this location
	mov si,ImageName
	call LoadFile	;loading the kernel
	mov dword [ImageSize],ecx	;saving the size of the kernel
	cmp ax,0	;if success then 
	je EnterStage3 ;enter stage 3
	mov si,msgFailure;else print error message and warm reboot
	call Puts16
	mov ah,0
	int 0x16	;await keypress
	int 0x19	;warm boot computer
	cli			; agar yaha pahuch gaye toh bhaari galti hogayi hai apun se
	hlt


	;=================================================
	;			Go into Protected mode
	;=================================================

	EnterStage3:

		cli;
		mov eax,cr0
		or eax,1
		mov cr0,eax
		jmp CODE_DESC:stage3 ;far jump to set the CS to 08h

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
	;		Copy kernel at 1mB mark
	;=================================================
	copyImage:
		mov eax,dword [ImageSize] ;contains the no of sectors
		movzx ebx,word [bpbBytesPerSector] 
		mul ebx	;convert it into bytes
		mov ebx,4	;we ar copying 4bytes at a time
		div ebx
		cld
		mov esi,IMAGE_RMODE_BASE
		mov edi,IMAGE_PMODE_BASE
		mov ecx,eax
		rep movsd

		;setup the data segments and stack 
		mov	ax, 0x10		; set data segments to data selector (0x10)
		mov	ds, ax
		mov	ss, ax
		mov	es, ax
		mov	esp, 90000h		; stack begins from 90000h


		call	ClrScr32
		;=================================================
		;			Execute the kernel
		;=================================================
		jmp CODE_DESC:IMAGE_PMODE_BASE

		cli
		hlt
