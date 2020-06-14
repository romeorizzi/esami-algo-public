#include <cstdio>
#include <cassert>

int tot = 0;

void f(int a, int b, int c) {
  tot = (tot+1)%1024;
  if(a>b) {
    f(a-1, b, c/2+1);
    f(a-1, b, c/2);
    f(a-5, b+5, c+1);
  }
}

int main() {
  #ifdef EVAL
      assert( freopen("input.txt", "r", stdin) );
      assert( freopen("output.txt", "w", stdout) );
  #endif

  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  f(a,b,c);
  printf("%d\n", tot);
  return 0;
}
