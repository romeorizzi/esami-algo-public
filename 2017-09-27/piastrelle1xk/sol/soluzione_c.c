/**
 *  Soluzione di piastrelle1xk 
 *
 *  Autore: Romeo Rizzi, 2017-09-25
 *
 *  soluzione iterativa
 *
 */

#include <assert.h>
#include <stdio.h>

#define MAXN 1000000
#define UNKNOWN 0

int memoRisp[MAXN +1];

int N, K;


int main() {
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );

  scanf("%d %d", &N, &K);

  for(int n = 0; n < K; n++)
    memoRisp[n] = 1;

  for(int n = K; n <= N; n++)
    memoRisp[n] = memoRisp[n-1] + memoRisp[n-K];
  
  printf("%d\n", memoRisp[N] ); 
  
  return 0;
}

