#include <cstdio>
#include <cassert>
#include <unordered_map>

using namespace std;

int memo[500][500][100];

int f(int a, int b, int c) {
  if(a<=b) return 1;
  if( memo[a][b][c] == 0 ) {
    memo[a][b][c] = (
      1 + f(a-1, b, c/2+1) + f(a-1, b, c/2) + f(a-5, b+5, c+1)      
    )%1024;
  }
  return memo[a][b][c];
}

int main() {
  #ifdef EVAL
      assert( freopen("input.txt", "r", stdin) );
      assert( freopen("output.txt", "w", stdout) );
  #endif

  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  printf("%d\n", f(a,b,c));
  return 0;
}
