#include <stdio.h>

long f(short a, int b, long c); 

int main(){
	short a;
        int  b;
	long c;
	printf(" Podaj trzy liczby : ");
	scanf("%hd %d %ld", &a, &b, &c);	
	printf(" Wynik : %ld \n", f(a, b, c));
	return 0;
}
