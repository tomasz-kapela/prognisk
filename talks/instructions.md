---
layout: default
nav_exclude: true
---

# Instrukcje asemblera


## Przenoszenie danych

* `MOV` - przenoszenie danych 
* `MOVZX` - przenieś i rozszerz zerami 
* `MOVSX` - przenieś i rozrzerz bitem znaku
* `XCHG` - wymienia wartości dwóch rejestrów

```asm
mov rax, 0x0102030405060708  ; rax = 0x01020304f5060708
mov rcx, -1                  ; rcx = 0xffffffffffffffff    
mov ax, cx                   ; rax = 0x01020304f506ffff, górne bity rax niezmienione 
mov ecx, eax                 ; rcx = 0x00000000f506ffff, górna połowa rcx wypełniona zerami
movsx rbx, eax               ; rbx = 0xfffffffff506ffff, rozszerzenie bitem znaku
movzx ebx, ax                ; rbx - 0x000000000000ffff, rozszerzenie zerami
xchg rcx, rax                ; rax = 0x00000000f506ffff   rcx = 0x01020304f506ffff  
```



### Rozserzanie bitem znaku liczb całkowitych 

* `CBW`    rozszerza AL do AX  
* `CWD`    rozszerza AX do DX:AX    
* `CDQ`    rozszerza EAX do EDX:EAX 
* `CWDE`   rozszerza AX do EAX      
* `CQO`    rozszerza RAX do RDX:RAX (tylko 64bit)

###

