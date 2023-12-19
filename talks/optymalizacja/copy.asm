

; RDI - dest
; RSI - src
; RDX - n

section .text

global copy_rep
copy_rep:
    cld
    mov rcx, rdx

    rep movsd
    ret


global copy_movsq
copy_movsq:
    cld
    mov rcx, rdx
    shr rcx, 1

    rep movsq
    ret


global copy_loop
copy_loop:
    cld
    mov rcx, rdx
.loop:
    movsd
    loop .loop
    ret


global copy_backward
copy_backward:
    mov rcx, rdx
.loop:
    mov eax, [rsi+4*rcx-4]
    mov [rdi+4*rcx-4], eax
    sub rcx, 1
    ; cmp rcx, 0
    jnz .loop
    ret

global copy_forward
copy_forward:
    mov rcx, 0
.loop:
    mov eax, [rsi+4*rcx-4]
    mov [rdi+4*rcx-4], eax
    add rcx, 1
    cmp rcx, rdx
    jnz .loop
    ret

global copy4
copy4:
	cld
    mov rcx, rdx
.loop:
    movsd
    sub rcx, 1
    ; cmp rcx, 0
    jnz .loop
    ret
