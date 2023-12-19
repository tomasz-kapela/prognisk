---
layout: default
parent: Wykłady
nav_order: 20
---

# Optymalizacja - suma - łancuch zależności

Zadanie polega na obliczeniu sumy elementów tablicy **tab** o danym **N** (operację powtarzamy **ITER** razy)

Programie [suma_dependancy.cpp](suma_dependancy.cpp) 
zdefiniowano kilka sposobów liczenia sumy. 
Sposób wybieramy definiując odpowiednie makro.

### SIMPLE

```cpp
sum = 0.0;
for (int i = 0; i < N; i++) 
  sum += tab[i];
```

### PREFETCH

* Cache'ujemy dane z odpowiednim wyprzedzeniem.
* Rozwijamy pętlę, tak aby w jednej iteracji wykorzystać cały wiersz cache. 
* Powielając zmienne, unikamy długiego ciągu zależności (kilka dodawań może wykonać się w jednym cyklu zegara).


```cpp
double  sum1 = 0., sum2 = 0., sum3 = 0., sum4 = 0.; 
for (int i = 0; i < N; i += 4){
  sum1 += tab[i];
  sum2 += tab[i+1];
  sum3 += tab[i+2]; 
  sum4 += tab[i+3];

  __builtin_prefetch(tab+i+16, 0, 3);  // (adres, rw (w=1), locality strength(1-3))
}
sum = (sum1 + sum2) + (sum3 + sum4);  
```

### VECTOR



```cpp

__m256d result = {0.0,0.0,0.0,0.0};

for(int i=0; i<N; i+= 4){
__m256d x = _mm256_loadu_pd(tab+i);
result = _mm256_add_pd(result, x);
}

double z[4] = {0.};
_mm256_storeu_pd(z, result);

sum = z[0]+z[1]+z[2]+z[3];
```

### Uzyskane czasy

| Wersja    | Małe      | Duże   | Duże |
|-----------|-----------|--------| ---|
| rozmiar N | 100       | 100000 | 100000 |
| ITER      | 150000000 | 15000 | 15000 |
| optymalizacja| -O3       | -O3 | -O0 |
| SIMPLE    | 7.69224s  | 1.37358s | 3.0922s |
| PREFETCH  | 2.59237s  | 0.361434s | 1.27144s |
| VECTOR    | 1.95894s  | 0.34297s | 1.44102s |

### Uruchomienie

```bash
make run_dependancy
```