;=================================================
;		Enable A20 line
;=================================================

%ifndef __A20_INC_FALCONOS_7999_INCLUDED_
%define __A20_INC_FALCONOS_7999_INCLUDED_
bits 16

EnableA20KeyboardDirect:
    cli
    push ax
    mov al,0xDD ;enable a20 address line
    out 0x64,al
    pop ax
    ret

EnableA20KeyboardOutputPort:
    cli
    pusha
        call WaitInput
        mov al,0xAD
        out 0x64,al ;keyboard band sabse phle
        call WaitInput

        mov al,0xD0
        out 0x64,al ;call for read output
        call WaitOutput

        in al,0x60
        push eax    ;iss value ko save kardo stack me aur dekho input buffer khaali ho
        call WaitInput

        mov al,0xD1
        out 0x64,al     ;ab kya karo usko bolo ki output port par likhna hai mujhe
        call WaitInput

        pop eax
        or al,2     ;ab usko likhdo buffer me
        out 0x60,al 
        call WaitInput

        mov al,0xAE
        out 0x64,al
        call WaitInput 
    popa
        sti
        ret

WaitInput:
    in al,0x64
    test al,2
    jnz WaitInput
    ret

WaitOutput:
    in al,0x64
    test al,1
    jz WaitOutput
    ret

    
%endif