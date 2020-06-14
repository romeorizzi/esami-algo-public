/**
 *  Soluzione di rightwards
 *
 *  Autore: Romeo Rizzi, 2018-02-10
 *
 *  Costo di questa soluzione: lineare, ottima.
 *
 *  Tecnica: programmazione dinamica
 * 
 *  Descrizione: per ogni riga r e colonna c della matrice introduciamo
 *  un sottoproblema opt[r,c] = massima somma su un cammino che parta dalla cella (r,c).
 * Questi problemi cadono da destra verso sinistra.
 * Viene comodo utilizzare i valori sentinella  opt[0,c] = 0, opt[M+1,c] = 0, opt[r,N+1] = 0
 */

#include <cassert>
#include <cstdio>

#define MAXM 500
#define MAXN 500

int M, N;
int val[MAXM+2][MAXN+2]; // matrice in input
int opt[MAXM+2][MAXN+2]; // tabella di programmazione dinamica
    //NOTA: in quanto variabile globale lo standard ANSI garantisce sia inizializzata tutta a zero.

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

    for(int c = N; c >= 1; c--)
      for(int r = 1; r <= M; r++) {
        opt[r][c] = opt[r][c+1];
        opt[r][c] = mymax( opt[r][c], opt[r+1][c+1] );
        opt[r][c] = mymax( opt[r][c], opt[r-1][c+1] );
	opt[r][c] += val[r][c]; 
      }
    
    int risp = opt[1][1];
    for(int r = 2; r <= M; r++)
        risp = mymax( risp, opt[r][1] );

    printf("%d\n", risp);
    
    return 0;
}

