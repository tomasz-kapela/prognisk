---
layout: default
nav_exclude: true
---


# Porównywanie liczb w SSE

## Porównania skalarne ustawiające flagi procesora

Poniższe instrukcje porównują skalarnie ostatnie elementy rejestrów i ustawiają odpowiednie flagi procesora `ZF`, `PF`, `CF`  (resztę zerują),
w ten sposób, że możemy następnie wykonywać odpwiednie skoki warunkowe jak dla liczb całkowitych bez znaku (`JE`, `JA`, `JB`, `JAE`,...)

```nasm
comiss/comisd   xmm1, xmm2     ; sygnalizuje błąd gdy argumentem jest QNaN lub SNaN
ucomiss/ucomisd xmm1, xmm2     ; sygnalizuje błąd tylko dla SNaN
```

Przykład

```nasm
comiss xmm0, xmm1    ; porównuje dwa floaty
jb etykieta          ; robi skok jeżeli xmm0[0] < xmm1[0]
```

## Porównania ustawiające maskę bitową

Gdy porównujemy odpowiadające elementy dwóch wektorów to wyniki porównania mogą się różnić dla poszczególnych par elementów.
Zamiast pojedynczego wyniku otrzymujemy na danej pozycji maskę bitową `111...11` gd porównanie zwróci prawdę lub `00...00` w przeciwnym wypadku.

### Liczby zmiennoprzecinkowe

```nasm
cmpps/cmppd a, b, XX    ; porównuje elementy wektorów a i b predykatem XX, maskę zapisuje w a
cmpss/cmpsd a, b, XX    ; porównuje skalarnie elementy a[0] i b[0] predykatem XX
vcmp** r, a, b, XX      ; porównuje wektory a i b podobnie jak cmp** ale maskę zapisuje w r  
```
Odpowiadające elementy dwóch wektorów (traktowane jako liczby float lub double) są porównywane i jeżeli zachodzi relacja  `a[i] XX b[i]` to wynikiem na danej pozycji jest maska `111...11` w przeciwnym wypadku `00...00`.  W przypadku instrukcji skalarnych porównywane są elementy z indeksem 0. 

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

*Przykład*. Testujemy, używając predykatu `<`, czy odpowiednie elementy wektora `xmm0`, traktowane jako liczby float, 
są mniejsze od odpowiednich elementów wektora `xmm1`. 
Przykładowo dla poniższych danych otrzymamy maskę

```nasm
cmpltps xmm0, xmm1    ;   równoznaczne cmpps xmm0, xmm1, 1

xmm0 : |   2.0   |  -4.3   |   36.4  |   12.1  |
xmm1 : |   7.0   |  -4.3   |    1.5  |   12.2  | 
            =         =         =         =
xmm0 : |111..1111|000..0000|000..0000|111..1111| ; (maska)
```

### Liczby całkowite 

Dla predykatu **XX (EQ, GT lub LT)** i tablicy liczb całkowitych ze znakiem o rozmiarze * **(B=1, W=2, D=4, Q=8)** 
wynikiem jest maska zawierająca jedynki dla tych elementów dla których predykat zwraca prawdę. 

```nasm
pcmpXX* a, b      ;  a[i] = (a[i] XX b[i])? 11...11 : 00...00     
vpcmpXX* w, a, b  ;  w[i] = (a[i] XX b[i])? 11...11 : 00...00
``` 

Przykład: w xmm1, xmm2 mamy ciągi 16 znaków (jednobajtowe = rozmiar B), chemy porównać je predykatem < (LT) wiec stosujemy instrukcję `PCMPLTB xmm1, xmm2`.

```nasm
pcmpltb xmm1, xmm2

xmm1 : A B C D E F G H I J K L M N O P
xmm2 : A A A F F F O O O O O O O O O O
 =     = = = = = = = = = = = = = = = =
xmm1 : 000000FFFF00FFFFFFFFFFFFFFFF0000 ; (maska)
```

## Eliminowanie skoków z wykorzystaniem masek

* Jeżeli dla elementów wektora v w zależności od spełnienia przez element predykatu `Pred` chcemy przeprowadzić różne obliczenia, których wyniki to odpowiednio Vt lub Vf. To nie pasuje do modelu SIMD.
* Chcemy uniknąć instrukcji warunkowej, bo ona wymusza wykonanie skalarne.

Rozwiązanie:
* Tworzymy maskę bitową `M` dla predykatu `Pred` i wektora `v` (ma jednyki na tych pozycjach gdzie spełniony jest predykat).
* Przeprowadzamy oba obliczenia dla całych wektorów otrzymująć wektory wyników `Vt` i `Vf`.
* Łączymy te wyniki wykorzystując maskę M i operacje bitowy
  ```
  ( Vt and M ) or ( Vf and !M )
  ``` 
  
Przykład

```nasm 
;  void change(const char * x){
;  for(int i=0; i<16; ++i)
;    if(x[i] <= 'M') x[i] = '*';
;  }
section .text 
change:
    movdqu  xmm0, [rdi]      ; ładujemy przekazany łańcuch tekstowy
    movdqu  xmm1, [const40]  ; wektor stałych 40
    movdqa  xmm2, xmm0       ; 
 
    pcmpgtb xmm2, xmm1       ; xmm2  zawiera maske
 
    movdqa  xmm1, [star]
 
    pand    xmm0, xmm2       ; zerujemy znaki mniejsze niż M      
    pandn   xmm2, xmm1       ; ustawiamy tam gwiazdki
    por     xmm0, xmm2       ; sumujemy 
 
    movdqu  [rdi], xmm0
 
    ret

section .data 
const40  'MMMMMMMMMMMMMMMM' 
star     '****************' 
```

## Maskowane przesyłanie danych

Aby wyeliminować skoki możemy też wykorzystać maskowane przesyłanie danych

```nasm
; Odczyt
vmaskmovps/pd xmm0, xmm1, [mem] ; wczytuje spod adresu `mem` te elementy wektora `xmm0` 
                                ; dla których w masce `xmm1` ustawione są jedynki, 
                                ; pozostałe elementy zeruje.
; Zapis
vmaskmovps/pd [mem], xmm1, xmm0 ; zapisuje pod adres `mem` te elementy wektora `xmm0` 
                                ; dla których w masce `xmm1` ustawione są jedynki, 
                                ; pozostałe elementy pozostają niezmienione.
```
