/**
 *  Soluzione ricorsiva esponenziale lenta di piastrelle1xk 
 *
 *  Autore: Romeo Rizzi, 2017-09-25
 *
 */

#include <assert.h>
#include <stdio.h>

#define MAXN 1000000

int N, K;

int numSol(int n) {
  // restituisce il numero di tilings di un rettangolo K x n con rettangoli 1 x K
  assert( n >= 0 );
  if( n < K ) return 1;
  return numSol(n-1) + numSol(n-K);
}  

int main() {
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );

  scanf("%d %d", &N, &K);

  printf("%d\n", numSol(N) ); 
  
  return 0;
}


