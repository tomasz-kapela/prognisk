
section .text
; RDI - dest
; RSI - src
; RDX - n
global copy
copy:
    cld
    ;;lea rcx, [4*rdx]
    ;;rep movsb
    
    
    mov rcx, rdx
    shr rcx, 1
    
    rep movsq
    
    mov rax, 0
    ret
