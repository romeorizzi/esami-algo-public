/* pirellone *
   solutore
   Roberto Grossi  2005-02-25
   updated Romeo 2015 (EVAL)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #define EVAL // define EVAL to input/output from file also in local

#define  MaxM   5000
#define  MaxN   5000

char P[MaxN][MaxM];     // Luci del Pirellone
char R[MaxN], C[MaxM];  // Interruttori di riga e colonna
int N, M, B, solvable;

void compriga( int i ){
  int j;
  for (j=0; j < M; j++)
    if (P[i][j])
      P[i][j] = 0;
    else
      P[i][j] = 1;
}

void compcol( int j ){
  int i;
  for (i=0; i < N; i++)
    if (P[i][j])
      P[i][j] = 0;
    else
      P[i][j] = 1;
}

int main(int argc, char *argv[]) {
  int i, j, x, row;
  FILE *in, *out;

#ifndef EVAL
  in = stdin;
  out = stdout;
#else
  in = fopen("input.txt", "r");
  out = fopen("output.txt", "w");
#endif

  if ( in == NULL || out == NULL )
    return 1;
  
  if ( fscanf(in, "%d %d %d", &N, &M, &B) != 3 )
    return 1;

  assert( 1 <= N && N <= MaxN );
  assert( 1 <= M && M <= MaxM );
  assert( 2 <= B && B <= 10 );

  /* Lettura input */

  row = -1;
  for ( i = 0 ; i < N ; i++ )
    for ( j = 0 ; j < M ; j++ ) {
      if ( fscanf(in, "%d", &x ) != 1 )
	return 1;
      if ( (P[i][j] = (char)x) )
	row = i;
    }
  assert ( row >= 0 && row < N );  // contiene almeno un 1

#ifdef DEBUG
  printf("%d %d\n", N, M);
  for ( i = 0 ; i < N ; i++ ){
    printf("%d", P[i][0]);
    for (j=1; j < M; j++)
      printf(" %d", P[i][j]);
    printf("\n");
  }
#endif

  /* Risoluzione */

  solvable = 1;

  for (i=0; i < N; i++)
    R[i] = 0;
  for (j=0; j < M; j++)
    C[j] = 0;

  for (j=0; j<M; j++)
    if (P[row][j]) {
      C[j] = 1;
      compcol( j );
    }

  for (i=0; i<N; i++)
    if (P[i][0]){
      R[i] = 1;
      compriga( i );
    }

  for ( i = 0 ; i < N ; i++ )
    for ( j = 0 ; j < M ; j++ )
      if (P[i][j])
	solvable = 0;

  if (!solvable){
    fprintf(out, "0");
    for (i=1; i < N; i++)
      fprintf(out, " 0");
    fprintf(out, "\n");
    fprintf(out, "0");
    for (j=1; j < M; j++)
      fprintf(out, " 0");
    fprintf(out, "\n");
  } else {
    fprintf(out, "%d", R[0]);
    for (i=1; i < N; i++)
      fprintf(out, " %d", R[i]);
    fprintf(out, "\n");
    fprintf(out, "%d", C[0]);
    for (j=1; j < M; j++)
      fprintf(out, " %d", C[j]);
    fprintf(out, "\n");
  }

  return 0;
}
