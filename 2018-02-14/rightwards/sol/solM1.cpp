/**
 *  Soluzione per il solo caso banale M=1 di rightwards
 *
 *  Autore: Romeo Rizzi, 2018-02-11
 *
 *  Costo di questa soluzione: lineare
 *
 */

#include <cassert>
#include <cstdio>

#define MAXM 500
#define MAXN 500

int M, N;
int val[MAXM+2][MAXN+2]; // matrice in input

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d %d", &M, &N);
    for(int r = 1; r <= M; r++)
      for(int c = 1; c <= N; c++)
        scanf("%d", &val[r][c]);

    int risp = 0;
    for(int c = 1; c <= N; c++)
       risp += val[1][c]; 

    printf("%d\n", risp);
    
    return 0;
}

