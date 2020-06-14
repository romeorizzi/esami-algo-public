/* pirelloneGFB *
   filename: farlocca
   Romeo Rizzi 2005-02-25

   contiene una soluzione farlocca con le seguenti funzionalità:
   1. offre allo studente un meccanismo semplice e fidato per la gestione dell' input/output
   2. quando sottomessa, consente di andare a comprendere il costo in tempo macchina di tale approccio alla lettura dell'input
   3. quando sottomessa, consente di farsi una mappa precisa di quali istanze siano non risolvibili
   4. consente di monitorare che le varie assunzioni e limiti sulle istanze siano tutti rispettati. 
*/

#include <cassert>
#include <cstdio>
#include <cstdlib>

// #define EVAL // define EVAL to input/output from file also in local

const int MaxM = 5000;
const int MaxN = 5000;

int P[MaxM][MaxN];     // Luci del Pirellone
int M, N, B;

int main(int argc, char *argv[]) {
#ifdef EVAL
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );
#endif
  if( scanf("%d %d %d", &M, &N, &B) != 3 )  return 1;
  assert( 1 <= M && M <= MaxM );
  assert( 1 <= N && N <= MaxN );
  assert( 2 <= B && B <= 10 );
  
  int non_zero_row = -1;
  for(int i = 0 ; i < M ; i++ )
    for(int j = 0 ; j < N ; j++ ) {
      if( scanf("%d", &P[i][j] ) != 1 )
	return 1;
      if( P[i][j] )
	non_zero_row = i;
    }
  assert ( non_zero_row >= 0 );  // verifica l'assunzione del testo che almeno una luce sia accesa.


  /* Risoluzione farlocca (assume che tutte le istanze siano non risolvibili) */

  printf("0");
  for(int i=1; i < M; i++)
    printf(" 0");
  printf("\n");
  printf("0");
  for(int j=1; j < N; j++)
    printf(" 0");
  printf("\n");

  return 0;
}
