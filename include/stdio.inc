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

bits 32

%define VIDMEM 0xB8000
%define COLS 80
%define ROWS 25
%define CHAR_ATRIB 14 ; black backgroud and white text

_CurrX db 0
_CurrY db 0

;=================================================
;           PutCh32
;			Put a char to screen
;=================================================

PutCh32:
    pusha
    mov edi,VIDMEM

    ;get current location
    xor eax,eax             ;clear eax
    mov ecx,2*COLS
    MOV al, BYTE [_CurrY]
    mul ecx
    push eax        ; calculated the 2*cols*currY

    xor eax,eax
    mov al, BYTE [_CurrX]
    mov cl,2
    mul cl
    pop ecx
    add eax,ecx
    xor ecx,ecx

    add edi,eax

    cmp bl, 0x0A
    je .Row

    ;print a character
    mov dl,bl
    mov dh,CHAR_ATRIB
    mov word[edi],dx

    ;update the next position
    inc byte [_CurrX]
    cmp byte [_CurrX],COLS
    je .Row
    jmp .done

.Row:
    mov byte [_CurrX],0
    inc byte [_CurrY]

.done:
    popa
    ret


;=================================================
;			Put string
;=================================================
PutS32:
    pusha
    push ebx
    pop edi ;edi point kar raha hai string pr

.loop:
    ;get the character into bl
    mov bl,byte [edi]
    cmp bl,0
    je .done

    ;print the character
    call PutCh32

    ;go to the next character
.next:
    inc edi
    jmp .loop

.done:
    mov bh,byte [_CurrY]
    mov bl,byte [_CurrX]
    call MovCur
    popa
    ret


;=================================================
;   Move cursor 
;   bh,bl me -> curY,curX hai
;=================================================
MovCur:
    pusha

    ; get the current postion
    xor eax,eax   ; abhi hame screen ke relative positon chhiye naaki bytes chahiye toh 
    mov al,bh       ;apun sida Y*cols+x karke ebx me store kardenge
    mov ecx,COLS
    mul ecx
    add al,bl
    mov ebx,eax

    ;=================================================
    ;			Setting the lowbyte in VGA
    ;=================================================
    mov al,0xf
    mov dx,0x3D4
    out dx,al

    mov al,bl
    mov dx,0x3D5
    out dx,al

    ;=================================================
    ;			Setting the highbyte in VGA
    ;=================================================
    xor eax,eax
    mov al,0xE
    mov dx,0x3D4
    out dx,al

    mov al,bh
    mov dx,0x3D5
    out dx,al

    popa
    ret

ClrScr32:
    pusha
    cld ;clears direction for stosw
    mov edi,VIDMEM
    mov cx,2000 ;because we have 2000 cells
    mov ah,CHAR_ATRIB
    mov al,' '
    rep stosw
    mov byte [_CurrX] ,0
    mov byte [_CurrY] ,0
    popa 
    ret




    

    


%endif ;__STDIO_INC_FALCONOS_7999_INCLUDED_
