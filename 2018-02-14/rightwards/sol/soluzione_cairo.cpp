#include <cassert>
#include <cstdio>
#include <algorithm>

using std::max;

int main() {
  assert( freopen("input.txt", "r", stdin) );
  assert( freopen("output.txt", "w", stdout) );

  int M, N;
  scanf("%d %d", &M, &N);

  int val[M+2][N+2]; // matrice in input
  for(int r = 1; r <= M; r++)
    for(int c = 1; c <= N; c++)
      scanf("%d", &val[r][c]);

  int d[M+2][N+2];

  for(int r = 0; r <= M+1; r++)
    d[r][N+1] = 0;
  for(int c = 0; c <= N+1; c++)
    d[0][c] = d[M+1][c] = 0;

  for(int c = N; c >= 1; c--)
    for(int r = 1; r <= M; r++)
      d[r][c] = val[r][c] + max(
        d[r][c+1],
        max(
          d[r+1][c+1],
          d[r-1][c+1]
        )
      );

  int risp = 0;
  for(int r = 1; r <= M; r++)
    risp = max(risp, d[r][1]);

  printf("%d\n", risp);

  return 0;
}
