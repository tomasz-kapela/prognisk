Title
===============================
{:.no_toc}

* TOC
{:toc}

Wstęp
-----
Funkcje intrinsics w C++ są inaczej nazywane funkcjami wbudowanymi. 
Są to krótkie funkcje, podobne do funkcji inline, 
które udostępniają specyficzne dla danej architektury operacje 
nie dostępne z poziomu języka C++ np. operacje wektorowe. 
Nie powodują one kosztów związanych z wywołaniem funkcji 
bo na ich podstawie kompilator tworzy kod w miejscu ich wywołania. 

Przeważnie dana funkcja intrinsics odpowiada jednej instrukcji asemblerowej, 
ale są wyjątki.

Funkcje intrinsics zastępują stosowane wcześniej wstawki asemblerowe, zapewniając większe bezpieczeństwo i czytelność kodu.

[Wprowadzenie do funkcji intrinsics na stronach Intela.](https://docs.microsoft.com/en-us/cpp/intrinsics/?view=msvc-170)

[Wygodny spis funkcji intrinsics stronie Intela](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html).

=== Typy danych 

* `__m64`  dana 64 bitowa
* `__m128` wektor 4 liczb typu float
* `__m128d` wektor dwóch liczb typu double
* `__m128i` wektor zawierający liczby całkowite: 16 liczb jedno bajtowych lub 8 słów lub 4 podwójne słowa itd

Zmienne tych typów mogą zostać umieszczone w jednym z rejestrów xmm0-xmm15 lub znajdować się w pamięci.

=== Przykład
```cpp
#include <x86intrin.h>
#include <cstdio>
using namespace std;

int main(){
  __m128 x = {1., 2., 3., 4.},    // __m128 jest tablicą 4 floatów
         y = {5., 7., 9., 11.},   
         result;  

  result = _mm_add_ps(x, y);      // ładujemy i dodajemy wektorowo 4 floaty 
  
  float z[4] = {0};
  _mm_storeu_ps(z, result);        // zapisujemy wynik w pamięci
    
  printf("[%f, %f, %f, %f]\n", z[0], z[1], z[2], z[3]);    
  return 0;
}
```

Drugą metodą jest operowanie wskaźnikami do __m128
```cpp
#include "emmintrin.h"
#include "xmmintrin.h"
#include <cstdio>

using namespace std;
int main(){

  float x[] = {1, 2, 3, 4};
  float y[] = {5, 7, 9, 11};
  float z[4];  

  __m128 *vx = (__m128 *) x, 
         *vy = (__m128 *) y,
         *vz = (__m128 *) z;

  *vz = _mm_add_ps(*vx, *vy);

  printf("[%f, %f, %f, %f]\n", z[0], z[1], z[2], z[3]);
  return 0;
}
```

W tym jednak wypadku ważne aby tablice były wyrównane do granicy 16 bajtowej bo zapis `*vx` jest zamieniany na `rozkaz movaps`.

Zadanie 1. 
----------
Przepisać poniższy program aby do wyznaczania maksimum używał funkcji intrinsics `_mm_max_epu32`

```cpp
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;
int main(){
  const int prog = 100000;
  const int rozmiar = 100;
  unsigned int tab[rozmiar];

  //srand(time(0));
  srand(2021);  // dla powtarzalności testów

  for(int i=0; i<rozmiar; ++i){
      tab[i] = rand() % prog;
  }
  unsigned int max = 0;
  for(int i=0; i<rozmiar; ++i){
      if(max < tab[i])
          max = tab[i];
  }
  printf("%d\n", max);
  return 0;
}
```

Zadanie 2.
----------
Przepisać zadanie 3 (skalowanie bitmapy) z zestawu SSE używając funkcji intrinsics.
```cpp
#include <stdio.h>

void scaleSSE(float * wynik, float * data, int n){
    /// TODO !!!!
    for(int i=0; i<n; ++i)
        wynik[i] = data[i];
}

int main(void){

    const int N=400,HL=1078;
    float data[N][N],
          wynik[N][N];
    unsigned char header[HL];
        int i,j;

    FILE *strm;
    strm=fopen("circle3.bmp","rb");
    fread(header, 1, HL, strm);  // wczytuje header
    for(i=0;i<N;i++)             // wczytuje dane bitmapy
        for(j=0;j<N;j++)         // konwertując piksele na float
            data[i][j]=(float)fgetc(strm);
    fclose(strm);

    // właściwe skalowanie bitmapy wiersz po wierszu
    for(i=0;i<N/2;i++)
        scaleSSE(wynik[i],data[2*i],N);
    
    // Modyfikujemy rozmiar bitmapy w nagłówku
    header[4]=0; header[3]=160; header[2]=118; // rozmiar pliku

    header[18]=200;   header[19]=0;  // szerokość bitmapy
    header[22]=200;   header[23]=0;  // wysokość bitmapy

    // Zapisuje wynik do pliku
    strm=fopen("wynik3.bmp","wb");
    fwrite(header, 1, HL, strm);
    for(i=0;i<N/2;i++)
        for(j=0;j<N/2;j++)    // konwertuje wyniki na skalę szarości
            fputc((unsigned char)wynik[i][j],strm);
    fclose(strm);
}
```
*Wskazówka*:
* Przy kompilacji należy dodać opcje definiującą odpowiednią architekturę docelową procesora w zależności od użytych funkcji.

Zadanie 3. 
----------

Zaimplementować filtry uwzględniające otoczenie tak jak opisano [tutaj](http://informatyka.wroc.pl/node/443?page=0,2).

*Wskazówki*: 
*  Dla każdego piksela liczymy średnią ważoną w jego otoczeniu 3x3 tzn.
   liczymy sumę pikseli z otoczenia przemnożonych przez odpowiednią wagę z macierzy
   weight, a następnie dzielimy przez sumę wag (chyba że suma wag jest zerem, to wtedy nie dzielimy).  
*  Wynik tych obliczeń może być poza zakresem [0,255], dlatego trzeba go odpowiednio "przyciąć".
*  Należy użyć funkcji wektorowych operujących na floatach.

Przykład użycia 
```cpp
#include <iostream>
#include <cmath>
using namespace std;
// width powinien dzielic sie przez 4
const int width = 300, height = 168;

void filtr(int imageWidth, int imageHeight, float image[height][width], 
           float weight[3][3], float result[height][width]){

  // TODO !!!

}

int main(void)
{
    const int headerLength = 122; // 64; //sizeof(BMPHEAD);
    char header[headerLength];
    float data[3][height][width];    // tablica dla każdej składowej koloru
    float result[3][height][width];

    float weight[3][3]= { {0, -2, 0}, { -2, 11, -2}, {0, -2, 0} };
    
    int i,j,k;
    FILE *file;
    file=fopen("pigeon.bmp","rb");
    if(!file) { std::cerr << " Error opening file !"; exit(1); }
    fread(header, headerLength, 1, file);
    for(i=0;i<height;i++)
        for(j=0;j<width;j++)
           for(k=0; k<3; ++k)   
            data[k][i][j]=fgetc(file);
    fclose(file);
    
    for(i=0;i<3;i++)   // filtrujemy dla każdej składowej osobno
        filtr(width, height, data[i], weight, result[i]);

    file=fopen("result.bmp","wb");
    fwrite(header, headerLength, 1, file);
    for(i=0;i<height;i++)
      for(j=0;j<width;j++)
        for(k=0; k<3; ++k)
          fputc((unsigned char)result[k][i][j],file);
    fclose(file);
}
```

Obrazek wejściowy [pigeon.bmp](pigeon.bmp)
