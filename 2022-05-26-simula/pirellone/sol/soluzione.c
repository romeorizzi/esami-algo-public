/* pirellone *
   solutore
   Romeo Rizzi  2015-02-05
*/

#include <stdio.h>
#define NDEBUG
#include <assert.h>

#define  MaxM   5000
#define  MaxN   5000

char R[MaxN], C[MaxM];  // Interruttori di riga e colonna
int M, N, solvable = 1;

void readDigitChar(char *var) {
  // reads the first digit. Also checks that the digit is either 0 or 1.
    do {
      if ( scanf("%c", var ) != 1 )  assert(0==1);
    } while( (*var < '0') || (*var > '9')  );
    assert( ( *var == '0' ) || ( *var == '1' ) );
}

int main(int argc, char *argv[]) {
#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int i, j;
  char x;
  if ( scanf("%d %d", &M, &N) != 2 )  return 1;
  assert( 1 <= M && M <= MaxM );
  assert( 1 <= N && N <= MaxN );
  
  for ( j = 0 ; j < N ; j++ )
    readDigitChar( &C[j] );

  R[0] = '0';
  for ( i = 1; i < M; i++ ) {
    readDigitChar( &R[i] );
    R[i] = ( C[0] == R[i] ) ? '0' : '1';
    if( R[i] == '0' )
       for ( j = 1 ; j < N ; j++ ) {
          readDigitChar( &x );
          if( x != C[j] ) { solvable = 0; i = M; j = N; }
       }
    else 
       for ( j = 1 ; j < N ; j++ ) {
          readDigitChar( &x );
          if( x == C[j] ) { solvable = 0; i = M; j = N; }
       }
  }

  if (!solvable){
    printf("0");
    for (i=1; i < M; i++)
      printf(" 0");
    printf("\n0");
    for (j=1; j < N; j++)
      printf(" 0");
    printf("\n");
  } else {
    printf("%c", R[0]);
    for (i=1; i < M; i++)
      printf(" %c", R[i]);
    printf("\n%c", C[0]);
    for (j=1; j < N; j++)
      printf(" %c", C[j]);
    printf("\n");
  }

  return 0;
}
