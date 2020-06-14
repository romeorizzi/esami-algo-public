#include <cassert>
#include <cstdio>
#include <algorithm>

#define MAXN 1000000
#define MAXK 1000000

int N;

int X[MAXN];

int count[MAXK];

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

  int sum = 0;
  for(int i = 0; i < N; i++) {
    count[X[i]] += 1;
    for(int k = 0; k < X[i]; k++) {
      count[X[i]] += count[k];
    }
    count[X[i]] %= MOD;
  }

  for(int k = 0; k <= K; k++) {
    sum += count[k];
    sum %= MOD;
  }

  printf("%d\n", sum);
  
  return 0;
}
