/**
 *  Soluzione farlocca di easyfall (illustra come curare input ed output)
 *
 *  Autore: Romeo Rizzi, 2017-09-25
 *
 */

#include <cassert>
#include <cstdio>

#define MAXN 1000000

int N;
int h[MAXN+1]; // altezze delle tessere

int main() {
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );

  scanf("%d", &N);
  for(int i = 1; i <= N; i++)
     scanf("%d", &h[i]);

  for(int i = 1; i <= N; i++)
    printf("%d ", i);    // giusto quando tutte le tessere sono alte 1. 
  printf("\n");
  
  return 0;
}

