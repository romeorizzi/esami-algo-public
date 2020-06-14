#include <cstdio>
#include <cassert>
#include <unordered_map>

using namespace std;

int memo[5000][5000];

int f(int a, int b) {
  if(a<=b) return 1;
  if( memo[a][b] == 0 ) {
    memo[a][b] = (
      1 + 2*f(a-1, b) + f(a-5, b + 5)
    )%1024;
  }
  return memo[a][b];
}

int main() {
  #ifdef EVAL
      assert( freopen("input.txt", "r", stdin) );
      assert( freopen("output.txt", "w", stdout) );
  #endif

  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  printf("%d\n", f(a,b));
  return 0;
}
