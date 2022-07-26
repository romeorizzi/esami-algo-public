#include <cassert>
#include <cstdio>

const int MAXN = 200;
const int MAXK = 200;
const int MOD=1000000007;

int g,N,K;
int s[MAXN]; // Gli indici della sequenza in input partono da 0.

int main() {
  scanf("%d %d %d", &g, &N, &K);
  int opt_val = 42;
  int num_opt_sols = 42;
  if(g==1)
    printf("%d\n", opt_val);
  else if(g==2)
    printf("%d\n", num_opt_sols);
  else
    assert(0);
        
  return 0;
}

