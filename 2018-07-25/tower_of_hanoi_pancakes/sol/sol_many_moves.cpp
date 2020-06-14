/**
 *  Soluzione parziale di tower_of_hanoi_pancakes che rinuncia ad impiegare il minimo numero di mosse 
 *
 *  Autore: Romeo Rizzi, 2018-06-10
 *
 */

#include <cassert>
#include <cstdio>

#define MAXN 100

int N;
int flip[MAXN +1]; // flip[i] = 1 se nello spostamento della torre la frittalla i deve ritrovarsi flippata, flip[i] = 0 altrimenti.
int flip2[MAXN +1]; // just a second copy for second use (flip gets spoiled with use)
int numMosse = 0;

void spostaDisco(int n, int from, int to) {
  printf("Muovi il disco %d dal piolo %d al piolo %d\n", n, from, to);
}

void conta_spostamentiDisco(int n, int from, int to) {
  numMosse++;
}  

void spostaTorre(int n, int from, int to, int aux, int flip[], void (*basicActionOnDisk) (int,int,int) ) {
  if(n <= 0) return;
  if( flip[n] ) {
    spostaTorre(n-1,  from, aux, to,  flip, basicActionOnDisk);
    (*basicActionOnDisk)(n, from, to);
    flip[n] = 1 - flip[n];
    spostaTorre(n-1,  aux, to, from,  flip, basicActionOnDisk);
  }
  else {
    spostaTorre(n-1,  from, to, aux,  flip, basicActionOnDisk);
    (*basicActionOnDisk)(n, from, aux);
    spostaTorre(n-1,  to, from, aux, flip, basicActionOnDisk);
    (*basicActionOnDisk)(n, aux, to);
    spostaTorre(n-1,  from, to, aux,  flip, basicActionOnDisk);
  }  
}  


int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
       scanf("%d", &flip[i]);
       if( flip[i] == 2 )
         flip[i] = 0;
       flip2[i] = flip[i];
    }   

    spostaTorre(N, 1,3,2, flip2, &conta_spostamentiDisco);
    printf("%d\n", numMosse );
    spostaTorre(N, 1,3,2, flip, &spostaDisco);
        
    return 0;
}


