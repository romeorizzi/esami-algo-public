/**
 *  Soluzione esponenziale (ricorsione pura) di rightwards
 *
 *  Autore: Romeo Rizzi, 2018-02-13
 *
 *  Costo di questa soluzione: esponenziale.
 *
 *  Tecnica: ricorsione pura
 * 
 *  Descrizione: per ogni riga r e colonna c della matrice consideriamo
 *  un sottoproblema opt(r,c) = massima somma su un cammino che parta dalla cella (r,c). Le righe e le colonne sono numerate a partire da 1
 * Questa famiglia di problemi e` chiusa rispetto ad induzione.
 * Base  opt(0,c) = 0, opt(M+1,c) = 0, opt(r,N+1) = 0
 */

#include <cassert>
#include <cstdio>

#define MAXM 500
#define MAXN 500

int M, N;
int val[MAXM+2][MAXN+2]; // matrice in input

int mymax(int a, int b) { return (a>b) ? a : b; }

int opt(int r, int c) {
  assert ( 0 <= r ); assert ( r <= M +1 );
  assert ( 0 < c ); assert ( c <= N +1 );
  if( r == 0 ) return 0;
  if( r == M+1 ) return 0;
  if( c == N+1 ) return 0;
  int risp = val[r][c] + mymax(
			         opt(r, c+1),
			         mymax( opt(r-1, c+1), opt(r+1, c+1) )
	         	      );
  //printf("opt( %d, %d ) = %d\n",  r, c, risp);
  return risp;
}

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d %d", &M, &N);
    for(int r = 1; r <= M; r++) //righe e colonne numerate a partire da 1
      for(int c = 1; c <= N; c++)
        scanf("%d", &val[r][c]);

    int risp = opt(1, 1);
    for(int r = 2; r <= M; r++)
      risp = mymax( risp, opt(r, 1) );

    printf("%d\n", risp);
    
    return 0;
}

