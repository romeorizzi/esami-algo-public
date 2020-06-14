/* pirellone *
   Da chiamare con
   ./generatore M N B p 1 seed tipo  per una configurazione con soluzione
   ./generatore M N B p 0 seed tipo  per una configurazione senza soluzione
   dove M e` il numero di righe e N e' il numero di colonne,
   B è la base. Ad esempio per B=2 viene prodotta una matrice binaria. 
   p in [1..99] e' la percentuale di sparsita' degli interruttori su cui agire,
   seed e' il seme iniziale per la funzione random,
   unico parametro opzionale: tipo, con valore di default tipo=0 e significato:
      tipo = 0 genera l'input, tipo = 1 genera l'output
   Roberto Grossi  2005-02-25, rivisto ed esteso a più riprese da Romeo Rizzi (last modified June 2018).
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define  MaxN   5000
#define  MaxM   5000

char P[MaxM][MaxN];     // Luci del Pirellone
char R[MaxM], C[MaxN];  // Interruttori di riga e colonna
int M, N, B, p, solvable, seed, tipo = 0;

void compriga(int i, int delta){
  int j;
  for (j=0; j < N; j++)
    P[i][j] = (P[i][j] + delta) % B;
}

void compcol(int j, int delta){
  int i;
  for (i=0; i < M; i++)
    P[i][j] = (P[i][j] + delta) % B;
}

int main(int argc, char *argv[]) {
  int i, j;

  if ( argc < 7 || argc > 8 ||
       sscanf(argv[1], " %d", &M) != 1 ||
       sscanf(argv[2], " %d", &N) != 1 ||
       sscanf(argv[3], " %d", &B) != 1 ||
       sscanf(argv[4], " %d", &p) != 1 ||
       sscanf(argv[5], " %d", &solvable) != 1 ||
       sscanf(argv[6], " %d", &seed) != 1 ||
       ((argc == 8) && (sscanf(argv[7], " %d", &tipo) != 1) ) ){
    printf("generatore M N B p 1 seed tipo, per una configurazione con soluzione\n");
    printf("generatore M N B p 0 seed tipo, per una configurazione senza soluzione\n");
    return 1;
  }

  srand( seed );
  
  assert( 1 <= M && M <= MaxM );
  assert( 1 <= N && N <= MaxN );
  assert( 2 <= B && B <= 10 );
  assert( 1 <= p && p <= 99 );
  assert( 0 <= tipo && tipo <= 1 );

  for (i=0; i < M; i++)
    for (j=0; j < N; j++)
      P[i][j] = 0;
  for (i=0; i < M; i++)
    R[i] = 0;
  for (j=0; j < N; j++)
    C[j] = 0;


  for (i=0; i < (M*p)/100; i++)
    R[ rand() % M ] = 1 + rand() % (B-1);
  for (j=0; j < (N*p)/100; j++)
    C[ rand() % N ] = 1 + rand() % (B-1);

  for (i=0; i < M; i++)
    if (R[i])
      compriga( i, R[i] );

  for (j=0; j < N; j++)
    if (C[j])
      compcol( j, C[j] );

  if (!solvable){
    i = rand() % M;
    j = rand() % N;

    P[i][j] = ( P[i][j]+1 ) % B;
  }

  if (!tipo) { // genera l'input  
    printf("%d %d %d\n", M, N, B);
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
