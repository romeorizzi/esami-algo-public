#include <cstdio>
#include <cassert>

int f(int a, int b, int c) {
  if(a<=b) {
    return 1;
  } else {
    return (
      1 + f(a-1, b, c/2+1) + f(a-1, b, c/2) + f(a-5, b+5, c+1)
    )%1024;
  }
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
