// KOMPILACJA - kod źródłowy C w main.c, kod źródłowy ASM w suma.asm
// LINUX :
// nasm -felf32 suma.asm -o suma.o
// gcc -m32 -o main.o -c main.c
// gcc -m32 main.o suma.o -o suma

#include <stdio.h>
int suma (int a, int b);         /* prototyp funkcji */
int main()
{
  int c=1, d=2;
  scanf("%d %d",&c,&d);
  printf("%d\n", suma(c,d));
  return 0;
}