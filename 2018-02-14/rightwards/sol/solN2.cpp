/**
 *  Soluzione per il solo caso banale N=2 di rightwards
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

int mymax(int a, int b) { return (a>b) ? a : b; }

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
    for(int r = 1; r <= M; r++) {
      risp = mymax( risp, val[r][1] + val[r][2] ); 
      risp = mymax( risp, val[r][1] + val[r-1][2] ); 
      risp = mymax( risp, val[r][1] + val[r+1][2] ); 
    }
    
    printf("%d\n", risp);
    
    return 0;
}

