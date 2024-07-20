;=================================================
;			For printing to the screen 	
;=================================================

%ifndef __STDIO_INC_FALCONOS_7999_INCLUDED_
%define __STDIO_INC_FALCONOS_7999_INCLUDED_

;=================================================
;			Print a nul terminated string
;           from DS:SI
;=================================================
bits 16
Puts16:
    pusha ;saves the registers
.Loop1:
    lodsb ;loads the char at al
    or al,al; it is 0 if null character
    jz Puts16Done
    mov ah,0eh ; for printing the character
    int 10h ;invoke bios and print
    jmp .Loop1
Puts16Done:
    popa
    ret


%endif ;__STDIO_INC_FALCONOS_7999_INCLUDED_
