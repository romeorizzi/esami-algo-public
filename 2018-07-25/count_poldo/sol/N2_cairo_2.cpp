#include <cassert>
#include <cstdio>

#define MAXN 1000000

int N;

int X[MAXN];
int count[MAXN];

const int MOD = 1024;

int main() {
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );

  scanf("%d", &N);
  for(int i = 0; i < N; i++) {
    scanf("%d", &X[i]);
  }

  int sum = 0;
  for(int i = N-1; i >= 0; i--) {
    count[i] = 1;
    for(int j = i+1; j < N; j++) {
      if(X[j] > X[i]) {
        count[i] += count[j];
        count[i] %= MOD;
      }
    }
    sum += count[i];
    sum %= MOD;
  }

  printf("%d\n", sum);
  
  return 0;
}
