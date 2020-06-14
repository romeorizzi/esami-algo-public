/**
 *  Soluzione farlocca di two_three_steps (illustra come curare input ed output)
 *
 *  Autore: Romeo Rizzi, 2018-06-14
 *
 */

#include <cassert>
#include <cstdio>

#define MAXN 1000000

int N;
int GGG[MAXN]; // GGG[i] = valore del ricordo i-esimo.

int main() {
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );

  scanf("%d", &N);
  for(int i = 0; i < N; i++)
     scanf("%d", &GGG[i]);

  printf("%d\n", 0); // giusto quando tutti i ricordi sono scialbi tranne al più il secondo. 
  
  return 0;
}

