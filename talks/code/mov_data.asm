global _start, lab
section .code
_start:
  mov rax, [rel a]
;  mov rbx, [b]

leb:
  mov [x], rbx
    mov     rax, 1          ; numer funkcji systemowej:
                            ; 1=sys_write - zapisz do pliku
    mov     rdi, 1          ; numer pliku, do którego piszemy.
                            ; 1 = standardowe wyjście = ekran
    mov     rsi, x      ; RSI = adres tekstu
    mov     rdx, 9    ; RDX = długość tekstu
    syscall                 ; wywołujemy funkcję systemową

  mov     rax, 60         ; numer funkcji systemowej
                          ; (60=sys_exit - wyjdź z programu)
  mov     rdi, 0          ; RDI - kod wyjścia
  syscall                 ; wywołujemy funkcję systemową


section data
    a db "12345678"
    b db "abcdefgh"
    x db "XXXXXXXX", 0ah