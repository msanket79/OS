section .text
    global getInterrupt

getInterrupt: ;parameter is in eax
    ; Save registers if needed
    push ebp
    mov ebp, esp
    ; The parameter `n` is on the stack at [ebp+8]
    mov eax, [ebp+8]
    mov byte  [getint +1],al
    mov esp, ebp
    pop ebp
    jmp getint
getint:
    int 0
    ret
    