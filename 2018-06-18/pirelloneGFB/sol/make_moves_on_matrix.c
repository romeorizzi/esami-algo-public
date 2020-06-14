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

int P[MaxM][MaxN];     // Luci del Pirellone
int R[MaxM], C[MaxN];  // Interruttori di riga e colonna
int M, N, B, solvable;

void shiftRow(int i, int delta){
  int j;
  for (j=0; j < N; j++)
    P[i][j] =  (P[i][j] + delta) %  B;
}

void shiftCol(int j, int delta ){
  int i;
  for (i=0; i < M; i++)
    P[i][j] =  (P[i][j] + delta) %  B;
}

int main(int argc, char *argv[]) {
  int i, j, x;
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
  
  if ( fscanf(in, "%d %d %d", &M, &N, &B) != 3 )
    return 1;

  assert( 1 <= M && M <= MaxM );
  assert( 1 <= N && N <= MaxN );
  assert( 2 <= B && B <= 10 );

  /* Lettura input */

  int non_zero_row = -1;
  for ( i = 0 ; i < M ; i++ )
    for ( j = 0 ; j < N ; j++ ) {
      if ( fscanf(in, "%d", &P[i][j] ) != 1 )
	return 1;
      if ( P[i][j] )
	non_zero_row = i;
    }
  assert ( non_zero_row >= 0 && non_zero_row < M );  // contiene almeno un 1


  /* Risoluzione */

  solvable = 1;

  for (i=0; i < M; i++)
    R[i] = 0;
  for (j=0; j < N; j++)
    C[j] = 0;

  for (j=0; j<N; j++) {
    if( P[0][j] ) {
      C[j] = B-P[0][j];
      shiftCol( j, C[j]);
    }  
    assert( P[0][j] == 0 );
  }

  for (i=0; i<M; i++) {
    if( P[i][0] ) {
      R[i] = B-P[i][0];
      shiftRow( i, R[i]);
    }
    assert( P[i][0] == 0 );
  }

  for ( i = 0 ; i < M ; i++ )
    for ( j = 0 ; j < N ; j++ )
      if (P[i][j])
	solvable = 0;

  if (!solvable){
    fprintf(out, "0");
    for (i=1; i < M; i++)
      fprintf(out, " 0");
    fprintf(out, "\n");
    fprintf(out, "0");
    for (j=1; j < N; j++)
      fprintf(out, " 0");
    fprintf(out, "\n");
  } else {
    fprintf(out, "%d", R[0]);
    for (i=1; i < M; i++)
      fprintf(out, " %d", R[i]);
    fprintf(out, "\n");
    fprintf(out, "%d", C[0]);
    for (j=1; j < N; j++)
      fprintf(out, " %d", C[j]);
    fprintf(out, "\n");
  }

  return 0;
}
