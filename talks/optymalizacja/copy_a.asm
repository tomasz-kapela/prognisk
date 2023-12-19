

; RDI - dest
; RSI - src
; RDX - n
global copy
copy:
    cld
    mov rcx, rdx
    rep movsd
    mov rax, 0
    ret
