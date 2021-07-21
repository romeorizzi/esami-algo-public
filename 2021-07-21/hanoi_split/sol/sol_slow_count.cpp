/**
 *  File: sol_slow_count.cpp
 *  Soluzione di hanoi_split col solo difetto di essere lenta quando si tratta di solo computare il minimo numero di mosse senza doverle eseguire. 
 *
 *  Autore: Romeo Rizzi, 2021-07-19
 *
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;
//const int DEBUG = 1;

typedef long long unsigned int llu;
char dest_peg[2] = {'C','B'}; // even disks should go to peg 'C', odd disks should go to peg 'B' 

int t, N;
llu numMoves = 0;

// implemento prima la simulazione (più facile, ci abbandoniamo agli stili descrittivo e ricorsivo)
void sposta_disco(int n, char peg_from, char peg_to, bool truly_act) {
  if(truly_act)
    printf("sposta il disco %d dal piolo %c al piolo %c\n", n, peg_from, peg_to);
  numMoves += 1;
}

void sposta_intera_torre(int n, char peg_from, char peg_to, char peg_aux, bool truly_act) {
  if(DEBUG) printf("CALLED: sposta_intera_torre(n=%d, peg_from=%c, peg_to=%c, peg_aux=%c)\n", n, peg_from, peg_to, peg_aux);
  if(n==0)
    return;
  else {
    sposta_intera_torre(n-1, peg_from, peg_aux, peg_to, truly_act);
    sposta_disco(n, peg_from, peg_to, truly_act);
    sposta_intera_torre(n-1, peg_aux, peg_to, peg_from, truly_act);
  }
}

char third_peg(char peg1, char peg2) {
  return 'A'+ (3 - (peg1-'A') - (peg2-'A') );
}

void split_intera_torre(int n, char peg_from, bool truly_act) {
  if(DEBUG) printf("CALLED: split_intera_torre(n=%d, peg_from=%cc)\n", n, peg_from);
  if(n==0)
    return;
  if(peg_from==dest_peg[n%2])
    split_intera_torre(n-1, peg_from, truly_act);
  else {
    char peg_aux = third_peg(peg_from, dest_peg[n%2]);
    sposta_intera_torre(n-1, peg_from, peg_aux, dest_peg[n%2], truly_act);
    sposta_disco(n, peg_from, dest_peg[n%2], truly_act);
    split_intera_torre(n-1, peg_aux, truly_act);
  }
}


int main() {
  scanf("%d%d", &t, &N);
  if(t==1)
    split_intera_torre(N, 'A', true);
  else {
    split_intera_torre(N, 'A', false);
    printf("%llu\n", numMoves);
  }        
  return 0;
}

