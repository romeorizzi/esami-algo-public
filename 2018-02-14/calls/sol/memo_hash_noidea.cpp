#include <cstdio>
#include <cassert>
#include <map>

using namespace std;

map<pair<pair<int, int>, int>, int> memo;

int f(int a, int b, int c) {
  if(a<=b) return 1;
  if( memo.find( make_pair(make_pair(a, b), c) ) == memo.end() ) {
    memo[ make_pair(make_pair(a, b), c) ] = (
      1 + f(a-1, b, c/2+1) + f(a-1, b, c/2) + f(a-5, b+5, c+1)
    )%1024;
  }
  return memo[ make_pair(make_pair(a, b), c) ];
}

int main() {
  #ifdef EVAL
      assert( freopen("input.txt", "r", stdin) );
      assert( freopen("output.txt", "w", stdout) );
  #endif

  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  printf("%d\n", f(a,b,c) );
  return 0;
}
