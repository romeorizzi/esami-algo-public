/**
 *  Un template per la soluzione di tower_of_hanoi_pancakes
 *
 *  Autore: Romeo Rizzi, 2018-07-19
 *
 */

#include <cassert>
#include <cstdio>

#define MAXN 100

int N;
int flip[MAXN +1]; // flip[i] = 1 se nello spostamento della torre la frittalla i deve ritrovarsi flippata, flip[i] = 0 altrimenti.

void spostaDisco(int n, int from, int to) {
  printf("Muovi il disco %d dal piolo %d al piolo %d\n", n, from, to);
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
       scanf("%d", &flip[i]);
    }   


    // soluzione corretta per N=1 quando nessuna frittella debba ritrovarsi infine flippata:
    printf("%d\n", 2 );
    spostaDisco(1, 1, 2);
    spostaDisco(1, 2, 3);
        
    return 0;
}

