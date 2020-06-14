#include <cstdio>
#include <cassert>

int f(int a, int b) {
  if(a<=b) {
    return 1;
  } else {
    return (
      1 + 2*f(a-1, b) + f(a-5, b + 5)
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
  printf("%d\n", f(a,b));
  return 0;
}
