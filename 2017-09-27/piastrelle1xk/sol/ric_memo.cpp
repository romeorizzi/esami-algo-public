/**
 *  Soluzione ricorsiva con memoizzazione piastrelle1xk 
 *
 *  Autore: Romeo Rizzi, 2017-09-25
 *
 */

#include <cassert>
#include <cstdio>

const int MAXN = 1000000;
const int UNKNOWN = 0;

int memoRisp[MAXN +1];

int N, K;

int numSol(int n) {
  // restituisce il numero di tilings di un rettangolo K x n con rettangoli 1 x K
  assert( n >= 0 );
  if( memoRisp[n] == UNKNOWN ) memoRisp[n] = numSol(n-1) + numSol(n-K);
  return memoRisp[n];
}  

int main() {
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );

  scanf("%d %d", &N, &K);

  for(int n = 0; n < K; n++)
    memoRisp[n] = 1;
  
  printf("%d\n", numSol(N) ); 
  
  return 0;
}

