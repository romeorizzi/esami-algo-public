#include <cstdio>
#include <cassert>
#include <map>

using namespace std;

map<pair<int, int>, int> memo;

int f(int a, int b) {
  if(a<=b) return 1;
  if( memo.find( make_pair(a, b) ) == memo.end() ) {
    memo[ make_pair(a, b) ] = (
      1 + 2*f(a-1, b) + f(a-5, b + 5)
    )%1024;
  }
  return memo[ make_pair(a, b) ];
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
