#include <stdio.h>
const int N = 100;

// na wyjściu out[i] = wiersz[i+1] - wiersz[i]
extern "C" void diff(char *out,char *wiersz, int n);

int main(void)
{
    char tab[N+1], DIFF[N];
    int i;

    tab[0]=1;

    for(i=1;i<=N;i++)
        tab[i]=tab[i-1]+i;

    diff(DIFF, tab, N);

    bool correct = true;
    for(i=0;i<N;i++){
        printf("%d ",DIFF[i]);
        if(((int)tab[i-1]-tab[i]<=-128) and (DIFF[i]!= -128)) correct=false;
        else if( DIFF[i] != i+1 ) correct = false;
    } 

    printf("\n");
    printf(correct?"OK\n":"ERROR!\n");
    return 0;
}

// OUT: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -128 17 18 19 20
