/* problem pirelloneGFB *
   file: soluzioneGF23.c   

   THIS IS PECISELY THE SAME AS soluzione.c
   EXCEPT for the added line:

     assert( B==2 || B==3 );

   PURPOUSE:
     it solves precisely those instances with the specified value of B. Though this limitation is artificial it allows to grade where the point for the subtasks are.

   Romeo Rizzi  2018-06-16
*/

// WARNING: Uses asserts with side-effects. If compiled with NDEBUG defined simply won't open the files. 
#include <assert.h>
#include <stdio.h>
#include <string.h>

// #define EVAL // to input/output from file also in local

#define  MaxN   5000
#define  MaxM   5000

char firstRowStringShiftedBy[10][2*MaxN +1]; // every possible shift in base B
char genRow[2*MaxN +5]; // who knows how the input has been generated, better play safe.
char solStringRowSwitches[2*MaxM +1];
char solStringColSwitches[2*MaxM +1];

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

  assert( B==2 || B==3 ); // *** ADDED LINE ***
    

  assert( fgets(firstRowStringShiftedBy[0], 2*MaxN +2, stdin) ); // first time to dry away the newline.
  assert( fgets(firstRowStringShiftedBy[0], 2*MaxN +2, stdin) );
  //printf(" -- First row (no shift): %s", firstRowStringShiftedBy[0]);

  int shift;
  for ( j = 0 ; j < N ; j++ ) {
    for (shift = 1; shift<B; shift++) {
      firstRowStringShiftedBy[shift][2*j] = ( firstRowStringShiftedBy[0][2*j] + shift < '0'+B ) ? firstRowStringShiftedBy[0][2*j] + shift : firstRowStringShiftedBy[0][2*j] + shift -B;
      firstRowStringShiftedBy[shift][2*j+1] = ' ';
    }  
  }
  for (shift = 1; shift<B; shift++) {
    firstRowStringShiftedBy[shift][2*N-1] = '\n';
    //printf("First row of shift %d: %s", shift, firstRowStringShiftedBy[shift]);
  }

  for ( j = 0 ; j < N ; j++ ) {
    solStringColSwitches[2*j] = '0' + ((B - (firstRowStringShiftedBy[0][2*j] -'0') ) % B);
    solStringColSwitches[2*j+1] = ' ';
  }  
  solStringColSwitches[2*N-1] = '\n'; // interruttori di colonna come scelti per annullare la prima riga
  //printf(" -- solStringColSwitches: %s", solStringColSwitches);
  
  solStringRowSwitches[0] = '0';
  solStringRowSwitches[1] = ' ';
  for ( i = 1; i < M; i++ ) {
    assert( fgets(genRow, 2*MaxN +2, stdin) );
    int shift = genRow[0] - firstRowStringShiftedBy[0][0];
    if(shift < 0)
      shift += B;
    //printf("i = %d, shift = %d\n", i, shift);
    if(strncmp(genRow, firstRowStringShiftedBy[shift], 2*N-1) != 0)  { solvable = 0; break; }
    int anti_shift = (B-shift)%B;
    solStringRowSwitches[2*i] = '0'+anti_shift;
    solStringRowSwitches[2*i+1] = ' ';
  }
  solStringRowSwitches[2*M-1] = '\n';
  //printf(" -- solStringRowSwitches: %s", solStringRowSwitches);

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
    printf("%s", solStringRowSwitches); // interruttori di riga
    printf("%s", solStringColSwitches); // interruttori di colonna come scelti per annullare la prima riga
  }

  return 0;
}
