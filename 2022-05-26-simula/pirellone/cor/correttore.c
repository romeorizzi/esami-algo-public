/* pirellone *
   correttore input answer
   Roberto Grossi  2005-02-25

   Qualche modifica di Flavio 2005-02-28
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//#define DEBUG
#define  MaxM   5000
#define  MaxN   5000

char R[MaxN], C[MaxM];    // Input: Interruttori di riga e colonna
char RR[MaxN], CC[MaxM];  // Answer: Interruttori di riga e colonna

int N, M, NN, MM;

void ex( char *msg, float res ) {
   if (msg) fprintf(stderr, "%s\n", msg);

   printf("%f\n", res);

   exit(0);
}

void complement( char a[], int size ){
  int i;
  for (i=0; i < size; i++)
    if (a[i])
      a[i] = 0;
    else
      a[i] = 1;
}

int compare( char a[], char b[], int size ){
  int i;
  for (i=0; i < size; i++)
    if ( a[i] != b[i] )
      return 0;
  return 1;
}

int main(int argc, char *argv[]) {
  int i, j, f;
  char c;
  FILE *in, *an;

  if ( argc != 4 ){
    fprintf( stderr, "correttore input correct user\n");
    return -100000;
  }

  /* correct answer */
  in = fopen( argv[2], "r");

  /* user answer */
  an = fopen( argv[3], "r");


  if ( in == NULL || an == NULL ){
    fprintf( stderr, "errore apertura file\n");
    return -100000;
  }


  /* Lettura output corretto */
  
  N = 0;
  do {
    f = fscanf(in, "%c", &c);
    if (f == EOF)
      break;
    if (f != 1)
      return 1;

    if ( c == ' ' || c == '\t' )
      continue;
    if ( c == '0' ) 
      R[N++] = 0;
    if ( c == '1' ) 
      R[N++] = 1;
  } while( c != '\n' );

  M = 0;
  do {
    f = fscanf(in, "%c", &c);
    if (f == EOF)
      break;
    if (f != 1)
      return 1;

    if ( c == ' ' || c == '\t' )
      continue;
    if ( c == '0' ) 
      C[M++] = 0;
    if ( c == '1' ) 
      C[M++] = 1;
  } while( c != '\n');

  /* Lettura output di test */

  NN = 0;
  do {
    f = fscanf(an, "%c", &c);
    if (f == EOF)
      break;
    if (f != 1)
      return 1;

    if ( c == ' ' || c == '\t' )
      continue;
    if ( c == '0' ) 
      RR[NN++] = 0;
    if ( c == '1' ) 
      RR[NN++] = 1;
  } while( c != '\n');
  assert( 1 <= NN && NN <= MaxN );

  MM = 0;
  do {
    f = fscanf(an, "%c", &c);
    if (f == EOF)
      break;
    if (f != 1)
      return 1;

    if ( c == ' ' || c == '\t' )
      continue;
    if ( c == '0' ) 
      CC[MM++] = 0;
    if ( c == '1' ) 
      CC[MM++] = 1;
  } while( c != '\n' );
  assert( 1 <= MM && MM <= MaxM );

  if ( N != NN || M != MM ) {
    ex("Numero errato di interruttori.", 0.0);
  }

#ifdef DEBUG
  printf("%d", R[0]);
  for (i=1; i < N; i++)
    printf(" %d", R[i]);
  printf("\n");
  printf("%d", C[0]);
  for (j=1; j < M; j++)
    printf(" %d", C[j]);
  printf("\n");
  printf("\n");
  
  printf("%d", RR[0]);
  for (i=1; i < NN; i++)
    printf(" %d", RR[i]);
  printf("\n");
  printf("%d", CC[0]);
  for (j=1; j < MM; j++)
    printf(" %d", CC[j]);
  printf("\n");
#endif

  if ( compare( R, RR, N ) || compare( C, CC, MM ) ) {
    ex("OK", 1.000);
  }

  complement( R, N );
  complement( C, M );

  if ( compare( R, RR, N ) || compare( C, CC, MM ) ) {
    ex("OK", 1.000);
  }

  ex("Output errato.", 0.0);
}
