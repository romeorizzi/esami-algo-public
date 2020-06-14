/* pirelloneGFB *
   filename: soluzione_saferead.cpp
   content: soluzione cauta nella lettura da file, valida per ogni B, lavora in streaming ma legge ed elabora un carattere alla volta.
   Romeo Rizzi  2018-06-15
*/

// WARNING: Uses asserts with side-effects. If compiled with NDEBUG defined simply won't open the files. 
#include <cassert>
#include <cstdio>
#include <cstdlib>     /* exit, EXIT_FAILURE */

// #define EVAL // to input/output from file also in local

#define  MaxM   5000
#define  MaxN   5000

int R[MaxM], C[MaxN];  // Interruttori di riga e colonna
int M, N, B, solvable = 1; // si assume risolvibile sino a prova contraria

inline void readDigitChar(int *risp) {
  // reads the first encounterd digit.
  // Also checks that this digit is in the range [0,B)
  char tmp;
  do {
    if ( scanf("%c", &tmp ) != 1 ) {
      printf ("Error while reading from input stream");
      exit (EXIT_FAILURE);
    }
  } while( (tmp < '0') || (tmp > '9')  );
  *risp = tmp - '0';
  if( *risp >= B) {
    printf ("Error while reading from input stream: the digit exceeds the base.");
    exit (EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
#ifdef EVAL
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );
#endif
  if ( scanf("%d %d %d", &M, &N, &B) != 3 )  return 1;
  assert( 1 <= M && M <= MaxM );
  assert( 1 <= N && N <= MaxN );
  assert( 2 <= B && B <= 10 );
  
  //printf( "Interruttori di colonna: \n");
  for (int j = 0 ; j < N ; j++ ) {
    int P0j;
    readDigitChar( &P0j );
    if(P0j)
      C[j] = B - P0j;
    // else C[j] = 0, as initialized (as global variable).
    //printf( "%d ", C[j] );
  }  //printf( "\n");

  //printf( "Interruttori di riga: \n");
  R[0] = 0; //printf( "%d ", R[0] );
  for(int i = 1; i < M; i++ ) {
    int Pi0;
    readDigitChar( &Pi0 );
    R[i] = (2*B -(Pi0+C[0]) ) % B; //printf( "%d ", R[i] );
    int Pij;
    for(int j = 1 ; j < N; j++ ) {
      readDigitChar( &Pij );
      //printf("check: i=%d j=%d Pij=%d R[i]=%d C[j]=%d --> %d\n", i, j, Pij, R[i], C[j], (Pij + R[i] + C[j]) % B );
      if( (Pij + R[i] + C[j]) % B ) { solvable = 0; break; }
    }
  }

  if (!solvable){
    printf("0");
    for(int i=1; i < M; i++)
      printf(" 0");
    printf("\n");
    printf("0");
    for(int j=1; j < N; j++)
      printf(" 0");
    printf("\n");
  } else {
    printf("%d", R[0]);
    for(int i=1; i < M; i++)
      printf(" %d", R[i]);
    printf("\n");
    printf("%d", C[0]);
    for(int j=1; j < N; j++)
      printf(" %d", C[j]);
    printf("\n");
  }

  return 0;
  //exit (EXIT_SUCCESS);
}
