---
layout: default
nav_exclude: true
---

# Optymalizacja kopiowania

Zadanie polega na skopiowaniu tablicy o danym *rozmiarze* (operację powtarzamy *N* razy)

Program główny [copy.c](copy.c) wywołuje funkcję zdefiniowaną w pliku [copy.asm](copy.asm) 
makrodefinicją `COPY`.

### Różne wersje kopiowania

```nasm
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
```

### Uzyskane czasy 

| Wersja         | Czasy       |  
|----------------|-------------|
| rozmiar        | 10000       |
| N              | 1000000     |
| `copy_rep`       | 0.698529    |
| `copy_loop`      | 18.695135   |
| `copy_movsq`     | 0.706954    |
| `copy_forward`   | 2.711850    |
| `copy_backward`  | 2.689194    |


### Uruchomienie

```bash
make run_copy
```