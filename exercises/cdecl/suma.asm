BITS 32
section .text
global suma        ; funkcja suma ma być widziana w innych modułach aplikacji
suma:
   enter 0, 0     ;  tworzymy ramkę stosu na początku funkcji
      ; ENTER 0,0 = PUSH EBP / MOV EPB, ESP
      ; po wykonaniu enter 0,0
      ; w [ebp]    znajduje się stary EBP
      ; w [ebp+4]  znajduje się adres powrotny z procedury
      ; w [ebp+8]  znajduje się pierwszy parametr,
      ; w [ebp+12] znajduje się drugi parametr
      ; itd.
; pomocnicze makrodefinicje
   %idefine    a    [ebp+8]
   %idefine    b    [ebp+12]
; tu zaczyna się właściwy kod funkcji
   mov    eax, a
   add    eax, b
; tu kończy się właściwy kod funkcji
   leave     ; usuwamy ramkę stosu LEAVE = MOV ESP, EBP / POP EBP
ret  ; wynik zwracany jest w rejestrze eax