/* pirellone *
   super fast solver based on "all raws are equal up to inversion"
   reads whole lines for fast input
   Romeo Rizzi  2015-02-05
*/

#include <stdio.h>
#define NDEBUG
#include <assert.h>
#include <string.h>

#define EVAL // to work with files also in local
#define  MaxM   5000
#define  MaxN   5000

char firstRow[2*MaxN +2];
char invFirstRow[2*MaxN +2];
char genRow[2*MaxN +2];
char firstCol[2*MaxM +2];

int M, N, solvable = 1;

int main(int argc, char *argv[]) {
#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int i, j;
  if ( scanf("%d %d", &M, &N) != 2 )  return 1;
  assert( 1 <= M && M <= MaxM );
  assert( 1 <= N && N <= MaxN );

  fgets(firstRow, 2*MaxN +2, stdin); // the first time is only to empy out the first line
  fgets(firstRow, 2*MaxN +2, stdin);
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
    fgets(genRow, 2*MaxN +2, stdin);
    firstCol[2*i] = genRow[0];
    firstCol[2*i+1] = ' ';
    if( firstCol[2*i] == firstRow[0]) {
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
    printf("\n0");
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
