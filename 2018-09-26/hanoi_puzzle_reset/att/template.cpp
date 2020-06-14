/**
 *  Un template per la soluzione di hanoi_tower_reset
 *
 *  Author: Romeo Rizzi, 2018-09-21
 *
 */

#include <cassert>
#include <cstdio>

const int BASE = 1000000;
const int MAXN = 30;

int N;
char pole[MAXN +1];
int numMoves = 0;

// USE THE FOLLOWING FUNCTION WHEN YOU ARE REQUIRED TO ACTUALLY SPECIFY EACH MOVE (n<=10)
void spostaDisco(int n, char from, char to) {
  assert(pole[n]==from);
  printf("Muovi il disco %d dal piolo %c al piolo %c\n", n, from, to);
  pole[n] = to;
}

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
       do
          scanf("%c", &pole[i]);
       while( pole[i] < 'A' || pole[i] > 'C');
    }


    spostaDisco(5, 'A', 'C');
    printf("%d\n", numMoves);
        
    return 0;
}

