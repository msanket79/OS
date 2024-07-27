%ifndef __COMMON_INC_FALCONOS_7999_INCLUDED_
%define __CONMON_INC_FALCONOS_7999_INCLUDED_

; where the kernel is to be loaded to in protected mode
%define IMAGE_PMODE_BASE 0x100000

; where the kernel is to be loaded to in real mode
%define IMAGE_RMODE_BASE 0x3000

; kernel name (Must be 11 bytes)
ImageName     db "KRNL    SYS"

; size of kernel image in bytes
ImageSize     db 0


%endif