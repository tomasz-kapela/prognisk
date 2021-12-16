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







