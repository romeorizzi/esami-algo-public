/* pirellone *
   Da chiamare con
   ./generatore M N p 1 seed output  per una configurazione con soluzione
   ./generatore M N p 0 seed output  per una configurazione senza soluzione
   dove M e` il numero di righe e N e' il numero di colonne, 
   p in [1..99] e' la percentuale di sparsita' degli interruttori su cui agire,
   seed e' il seme iniziale per la generazione pseudo-random,
   output = 0 genera l'input, output = 1 genera l'output
   Roberto Grossi  2005-02-25, Romeo Rizzi  2022-05-25 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define  MaxN   5000
#define  MaxM   5000

char P[MaxM][MaxN];     // Luci del Pirellone
char R[MaxM], C[MaxN];  // Interruttori di riga e colonna
int M, N, p, solvable, seed, output;

void compriga( int i ){
  int j;
  for (j=0; j < N; j++)
    if (P[i][j])
      P[i][j] = 0;
    else
      P[i][j] = 1;
}

void compcol( int j ){
  int i;
  for (i=0; i < M; i++)
    if (P[i][j])
      P[i][j] = 0;
    else
      P[i][j] = 1;
}

int main(int argc, char *argv[]) {
  int i, j, ii, jj;

  if ( argc != 7 ||
       sscanf(argv[1], " %d", &M) != 1 ||
       sscanf(argv[2], " %d", &N) != 1 ||
       sscanf(argv[3], " %d", &p) != 1 ||
       sscanf(argv[4], " %d", &solvable) != 1 ||
       sscanf(argv[5], " %d", &seed) != 1 ||
       sscanf(argv[6], " %d", &output) != 1 ){
    printf("generatore M N p 1 seed output, per una configurazione con soluzione\n");
    printf("generatore M N p 0 seed output, per una configurazione senza soluzione\n");
    return 1;
  }

  srand( seed );
  
  assert( 1 <= M && M <= MaxM );
  assert( 1 <= N && N <= MaxN );
  assert( 1 <= p && p <= 99 );
  assert( 0 <= output && output <= 1 );

  for (i=0; i < M; i++)
    for (j=0; j < N; j++)
      P[i][j] = 0;
  for (i=0; i < M; i++)
    R[i] = 0;
  for (j=0; j < N; j++)
    C[j] = 0;


  for (i=0; i < (M*p)/100; i++)
    R[ rand() % M ] = 1;
  for (j=0; j < (N*p)/100; j++)
    C[ rand() % N ] = 1;

  for (i=0; i < M; i++)
    if (R[i])
      compriga( i );

  for (j=0; j < N; j++)
    if (C[j])
      compcol( j );

  if (!solvable){
    ii = i = rand() % M;
    while(ii==i) ii = rand() % M;
    jj = j = rand() % N;
    while(jj==j) jj = rand() % N;

    P[i][j] = 0;
    P[i][jj] = 1;
    P[ii][j] = 1;
    P[ii][jj] = 1;
  }

  if (!output) { // genera l'input  
    printf("%d %d\n", M, N);
    for ( i = 0 ; i < M ; i++ ){
      printf("%d", P[i][0]);
      for (j=1; j < N; j++)
	printf(" %d", P[i][j]);
      printf("\n");
    }
  } else { // genera l'output
    if (!solvable){
      printf("0");
      for (i=1; i < M; i++)
	printf(" 0");
      printf("\n");
      printf("0");
      for (j=1; j < N; j++)
	printf(" 0");
      printf("\n");
    } else {
      printf("%d", R[0]);
      for (i=1; i < M; i++)
	printf(" %d", R[i]);
      printf("\n");
      printf("%d", C[0]);
      for (j=1; j < N; j++)
	printf(" %d", C[j]);
      printf("\n");
    }
  }

  return 0;
}
