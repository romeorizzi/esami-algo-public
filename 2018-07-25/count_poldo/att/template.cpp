#include <cassert>
#include <cstdio>

#define MAXN 1000000

int N;

int X[MAXN];

int main() {
#ifdef EVAL
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );
#endif

  scanf("%d", &N);
  for(int i = 0; i < N; i++) {
    scanf("%d", &X[i]);
  }

  int count;

  count = 0;

  printf("%d\n", count);
  return 0;
}

