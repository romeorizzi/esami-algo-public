/**
 *  File: soluzione.cpp
 *  Soluzione di riferimento per hanoi_split
 *  Romeo Rizzi, 2021-07-19
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;
//const int DEBUG = 1;

typedef long long unsigned int llu;
char dest_peg[2] = {'C','B'}; // even disks should go to peg 'C', odd disks should go to peg 'B' 

int t, N;

// implemento prima la simulazione (più facile, ci abbandoniamo agli stili descrittivo e ricorsivo)
void sposta_disco(int n, char peg_from, char peg_to) {
  printf("sposta il disco %d dal piolo %c al piolo %c\n", n, peg_from, peg_to);
}

void sposta_intera_torre(int n, char peg_from, char peg_to, char peg_aux) {
  if(DEBUG) printf("CALLED: sposta_intera_torre(n=%d, peg_from=%c, peg_to=%c, peg_aux=%c)\n", n, peg_from, peg_to, peg_aux);
  if(n==0)
    return;
  else {
    sposta_intera_torre(n-1, peg_from, peg_aux, peg_to);
    sposta_disco(n, peg_from, peg_to);
    sposta_intera_torre(n-1, peg_aux, peg_to, peg_from);
  }
}

char third_peg(char peg1, char peg2) {
  return 'A'+ (3 - (peg1-'A') - (peg2-'A') );
}

llu num_moves_to_move_a_whole_tower(int n) {
  if(n==0)
    return 0;
  else
    return 2*num_moves_to_move_a_whole_tower(n-1) +1;
}

llu split_intera_torre(int n, char peg_from, bool truly_act) {
  if(DEBUG) printf("CALLED: split_intera_torre(n=%d, peg_from=%cc)\n", n, peg_from);
  if(n==0)
    return 0;
  if(peg_from==dest_peg[n%2])
    return split_intera_torre(n-1, peg_from, truly_act);
  char peg_aux = third_peg(peg_from, dest_peg[n%2]);
  if(truly_act) {
    sposta_intera_torre(n-1, peg_from, peg_aux, dest_peg[n%2]);
    sposta_disco(n, peg_from, dest_peg[n%2]);
    return num_moves_to_move_a_whole_tower(n-1) +1 + split_intera_torre(n-1, peg_aux, truly_act);
  }
  else return num_moves_to_move_a_whole_tower(n-1) +1 +split_intera_torre(n-1, peg_aux, truly_act);
}


int main() {
  scanf("%d%d", &t, &N);
  if(t==1)
    split_intera_torre(N, 'A', true);
  else
    printf("%llu\n", split_intera_torre(N, 'A', false));
  return 0;
}

