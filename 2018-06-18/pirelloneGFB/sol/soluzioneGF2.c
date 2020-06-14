/* pirelloneGFB *
   
   super fast solver based on "all raws are equal up to inversion"
   reads whole lines for fast input
   works in streaming
   works only for the binary case GF(2). This limitation follows by the way it has been written.
   Romeo Rizzi  2018-06-16
*/

// WARNING: Uses asserts with side-effects. If compiled with NDEBUG defined simply won't open the files. 
#include <assert.h>
#include <stdio.h>
#include <string.h>

// #define EVAL // to input/output from file also in local

#define  MaxN   5000
#define  MaxM   5000

char firstRow[2*MaxN +2];
char invFirstRow[2*MaxN +2];
char genRow[2*MaxN +2];
char firstCol[2*MaxM +2];

int M, N, B, solvable = 1;

int main(int argc, char *argv[]) {
#ifdef EVAL
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );
#endif
  int i, j;
  assert( scanf("%d %d %d", &M, &N, &B) == 3 );
  assert( 1 <= M && M <= MaxM );
  assert( 1 <= N && N <= MaxN );
  assert( 2 <= B && B <= 10 );

  assert( fgets(firstRow, 2*MaxN +2, stdin) );
  assert( fgets(firstRow, 2*MaxN +2, stdin) );
//printf(" -- First row: %s", firstRow);

  for ( j = 0 ; j < N ; j++ ) {
    invFirstRow[2*j] = ( firstRow[2*j] == '1' ) ? '0' : '1';
    invFirstRow[2*j+1] = ' ';
  }
  invFirstRow[2*N] = '\n';
//printf("Inv first row: %s", invFirstRow);
  
  firstCol[0] = firstRow[0];
  firstCol[1] = ' ';
  for ( i = 1; i < M; i++ ) {
    assert( fgets(genRow, 2*MaxN +2, stdin) );
    firstCol[2*i] = genRow[0];
    firstCol[2*i+1] = ' ';
    if( firstCol[2*i] == firstCol[0]) {
      if(strncmp(genRow, firstRow, 2*N-1) != 0)  { solvable = 0; i = M; }
    }
    else 
      if(strncmp(genRow, invFirstRow, 2*N-1) != 0)  { solvable = 0; i = M; }
  }
  firstCol[2*M] = '\n';
//printf(" -- First col: %s", firstCol);

  if (!solvable){
    printf("0");
    for (i=1; i < M; i++)
      printf(" 0");
    printf("\n");
    printf("0");
    for (j=1; j < N; j++)
      printf(" 0");
    printf("\n");
  }
  else {
    printf("%s", firstCol);
    if(firstCol[0] == '0') 
      printf("%s", firstRow);
    else
      printf("%s", invFirstRow);
  }

  return 0;
}
