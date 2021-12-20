# Porównywanie liczb w SSE

## Porównywanie skalarne ustawiające flagi procesora

Poniższe instrukcje porównują skalarnie ostatnie elementy rejestrów i ustawiają odpowiednie flagi procesora `ZF`, `PF`, `CF`  (resztę zerują),
w ten sposób, że możemy następnie wykonywać odpwiednie skoki warunkowe jak dla liczb całkowitych bez znaku (`JE`, `JA`, `JB`, `JAE`,...)
```nasm
comiss, comisd      ; sygnalizuje błąd gdy argumentem jest QNaN lub SNaN
ucomiss, ucomisd    ; sygnalizuje błąd tylko dla SNaN
```

Przykład
```nasm
   comiss xmm0, xmm1    ; porównuje dwa floaty
   jb etykieta          ; robi skok jeżeli xmm0[0] < xmm1[0]
```

## Porównywanie ustawiające maskę 

```
cmpps / cmppd a, b, XX    ; porównuje elementy wektorów a i b predykatem XX
cmpss / cmpsd a, b, XX    ; porównuje skalarnie elementy a[0] i b[0] predykatem XX
```
Odpowiadające elementy dwóch wektorów są porównywane i jeżeli zachodzi relacja  `a[i] XX b[i]` to wynikiem na danej pozycji jest maska `111...11` w przeciwnym wypadku `00...00`.  W przypadku instrukcji skalarnych porównywane są elementy z indeksem 0. 
```
a[i] = (a[i] XX b[i]) ? 0xFF..FF :  0x00..00;
```

Najczęściej wykorzystywane predykaty i odpowiadające im pseoudoinstrukcje (są zamieniane przez kompilator na instrukcję z odpowiednią stałą XX).
| XX | predykat | pseudoinstrucja |
| ---| -----    |  ----           |  
|  0 |  =       | CMPEQ**         |    
|  1 |  <       | CMPLT**         |    
|  2 |  <=      | CMPLE**         |    
|  3 |  isnan   | CMPUNORD**      |    
|  4 |  !=      | CMPNEQ**        |    
|  5 |  >       | CMPNLT**        |    
|  6 |  >=      | CMPNLE**        |    
|  7 |  !isnan  | CMPORD**        |    

Przykład testowania, czy liczby są różne (rozkaz CMPNEQPS xmm0, xmm1):
```
 +---------+---------+---------+---------+
 |   1.0   |  -5.3   |   16.5  |   17.2  | xmm0
 +---------+---------+---------+---------+
      ≠         ≠         ≠         ≠
 +---------+---------+---------+---------+
 |   7.0   |  -5.3   |   16.5  |   17.3  | xmm1
 +---------+---------+---------+---------+
      =         =         =         =
 +---------+---------+---------+---------+
 |111..1111|000..0000|000..0000|111..1111| xmm0
 +---------+---------+---------+---------+
```



