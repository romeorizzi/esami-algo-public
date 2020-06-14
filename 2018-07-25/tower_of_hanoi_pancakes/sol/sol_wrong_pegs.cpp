/**
 *  Soluzione parziale di tower_of_hanoi_pancakes. Unico problema: sbaglia i pegs in funzione spostaDisco
 *
 *  Autore: Romeo Rizzi, 2018-07-18
 *
 */

#include <cassert>
#include <cstdio>

#define MAXN 100

int N;
int flip[MAXN +1]; // flip[i] = 1 se nello spostamento della torre la frittalla i deve ritrovarsi flippata, flip[i] = 0 altrimenti.
int numMosse = 0;

void spostaDisco(int n, int from, int to) {
  printf("Muovi il disco %d dal piolo %d al piolo %d\n", n, from, 6-from-to); // sbaglia il peg di destinazione
}

void conta_spostamentiDisco(int n, int from, int to) {
  numMosse++;
}  

void spostaTorre(int n, int from, int to, int aux, int requires_extra_move[], void (*basicActionOnDisk) (int,int,int) ) {
  if(n <= 0) return;
  if( requires_extra_move[n] ) {
    spostaTorre(n-1,  from, to, aux,  requires_extra_move, basicActionOnDisk);
    (*basicActionOnDisk)(n, from, aux);
    spostaTorre(n-1,  to, from, aux, requires_extra_move, basicActionOnDisk);
    (*basicActionOnDisk)(n, aux, to);
    spostaTorre(n-1,  from, to, aux,  requires_extra_move, basicActionOnDisk);
    requires_extra_move[n] = 0;
  }
  else {
    spostaTorre(n-1,  from, aux, to,  requires_extra_move, basicActionOnDisk);
    (*basicActionOnDisk)(n, from, to);
    spostaTorre(n-1,  aux, to, from,  requires_extra_move, basicActionOnDisk);
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
    }   

    int requires_extra_move_to_fix_parity[MAXN +1];
    if( flip[N] == 2 )
      requires_extra_move_to_fix_parity[N] = 0;
    else
      requires_extra_move_to_fix_parity[N] = 1 - flip[N];
    
    for(int i = N-1; i >= 1; i--) {
      if( flip[i] == 2 )
        requires_extra_move_to_fix_parity[i] = 0;
      else
        requires_extra_move_to_fix_parity[i] = (flip[i] + requires_extra_move_to_fix_parity[i+1]) %2;
    }   
    int copy2_requires_extra_move_to_fix_parity[MAXN +1]; // just a second copy for second use (it gets spoiled with use)
    for(int i = 1; i <= N; i++) {
       copy2_requires_extra_move_to_fix_parity[i] = requires_extra_move_to_fix_parity[i];
    }   

    spostaTorre(N, 1,3,2, requires_extra_move_to_fix_parity, &conta_spostamentiDisco);
    printf("%d\n", numMosse );
    spostaTorre(N, 1,3,2, copy2_requires_extra_move_to_fix_parity, &spostaDisco);
        
    return 0;
}

