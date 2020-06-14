#include <cassert>
#include <cstdio>
#include <algorithm>

#define MAXN 1000000
#define MAXK 1000000

int N;

int X[MAXN];

int FT[MAXK+2];

const int MOD = 1024;

int main() {
#ifdef EVAL
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );
#endif

  int K = 0;

  scanf("%d", &N);
  for(int i = 0; i < N; i++) {
    scanf("%d", &X[i]);
    K = std::max(K, X[i]);
  }

  for(int i = 0; i < N; i++) {
    int x = X[i];

    int count = 0;
    for(int k = x; k > 0; k-=((k)&(-k))) {
      count += FT[k];
      count %= MOD;
    }

    for(int k = x+1; k <= K+1; k+=((k)&(-k))) {
      FT[k] += 1 + count;
      FT[k] %= MOD;
    }
  }

  int sum = 0;
  for(int k = K+1; k > 0; k-=((k)&(-k))) {
    sum += FT[k];
    sum %= MOD;
  }

  printf("%d\n", sum);
  
  return 0;
}
