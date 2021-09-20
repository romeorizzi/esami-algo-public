/**
 *  File: soluzione.cpp
 *  Soluzione di riferimento per hanoi_with_split_merge
 *  Romeo Rizzi, 2021-09-17
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;
//const int DEBUG = 1;

int t, t1, N;

typedef long long unsigned int llu;

llu moves_counter = 0;

// implemento prima la simulazione (più facile, ci abbandoniamo agli stili descrittivo e ricorsivo)
void sposta_disco(int n, char peg_from, char peg_to) {
  moves_counter++;
  printf("sposta il disco %d dal piolo %c al piolo %c\n", n, peg_from, peg_to);
}

void sposta_torre_classic(int n, char peg_from, char peg_to, char peg_aux) {
  if(DEBUG) printf("CALLED: sposta_torre_classic(n=%d, peg_from=%c, peg_to=%c, peg_aux=%c)\n", n, peg_from, peg_to, peg_aux);
  if(n==0)
    return;
  else {
    sposta_torre_classic(n-1, peg_from, peg_aux, peg_to);
    sposta_disco(n, peg_from, peg_to);
    sposta_torre_classic(n-1, peg_aux, peg_to, peg_from);
  }
}

void split_dal_disco(int i, char peg_from, char peg_dest1, char peg_dest2) {
  moves_counter++;
  printf("split il piolo %c, dal disco %d, sui pioli %c e %c\n", peg_from,i,peg_dest1,peg_dest2);
}

void merge_dal_disco(int i, char peg_dest, char peg_from1, char peg_from2) {
  moves_counter++;
  printf("merge sul piolo %c, dal disco %d del piolo %c e dal piolo %c\n", peg_dest,i,peg_from1,peg_from2);
}
    
void sposta_torre_with_balanced_moves(int n, char peg_from, char peg_to, char peg_aux) {
  /*   assume che tutti i dischi i <= n siano uno sopra l'altro in torre sul peg <peg_from>.
       Sposta questa intera torre sul peg <peg_to>, secondo l'unica soluzione ottima.
       Si assume che <peg_aux> indichi il terzo peg.   */
  if(n == 0) return;
  if(n%2) {
    sposta_torre_with_balanced_moves(n-1, peg_from, peg_aux, peg_to);
    sposta_disco(n, peg_from, peg_to);
    sposta_torre_with_balanced_moves(n-1, peg_aux, peg_to, peg_from);
  } else { // n%2==0 (even number of disks)
    split_dal_disco(n, peg_from, peg_to, peg_aux);
    if(n == 2) sposta_disco(n-1, peg_aux, peg_to);
    else { // n >= 4
      merge_dal_disco(n-2, peg_from, peg_to, peg_aux);
      sposta_disco(n-1, peg_aux, peg_to);
      sposta_torre_with_balanced_moves(n-2, peg_from, peg_to, peg_aux);
    }
  }
}

void sposta_torre_with_all_moves(int n, char peg_from, char peg_to, char peg_aux) {
  /*   assume che tutti i dischi i <= n siano uno sopra l'altro in torre sul peg <peg_from>.
       Sposta questa intera torre sul peg <peg_to>, secondo l'unica soluzione ottima.
       Si assume che <peg_aux> indichi il terzo peg.   */
  if(n == 0) return;
  if(n == 1) sposta_disco(1, peg_from, peg_to);
  else {
    split_dal_disco(n, peg_from, peg_to, peg_aux);
    if(n == 2) sposta_disco(n-1, peg_aux, peg_to);
    if(n == 3 || n == 4) {
      sposta_disco(n-2, peg_to, peg_from);
      merge_dal_disco(n-1, peg_to, peg_aux, peg_from);
    }
    if(n >= 5) {
      merge_dal_disco(n-2, peg_from, peg_to, peg_aux);
      sposta_disco(n-1, peg_aux, peg_to);
      sposta_torre_with_all_moves(n-2, peg_from, peg_to, peg_aux);
    }
  }
}

llu num_moves(int t1, int n) {
  //printf("called num_moves(t1=%d,n=%d)\n",t1,n);
  assert(n >= 0);
  if(n <= 1) return n;
  if(t1==0) return 1+2*num_moves(t1,n-1);
  if(n == 2) return 2;
  if(t1==1)
    if(n%2==1) return 2*num_moves(t1,n-1) +1;
    else return 3+num_moves(t1,n-2);
  if(t1==2)
    if(n <= 4) return 3;
    else return 3+num_moves(t1,n-2);
}


int main() {
  scanf("%d%d%d", &t, &t1, &N);
  if(t==0)
    printf("%llu\n", num_moves(t1,N));
  else {
    if(t1==0) {
      sposta_torre_classic(N, 'A', 'C', 'B');
      assert(moves_counter == num_moves(t1,N));
    }
    if(t1==1) {
      sposta_torre_with_balanced_moves(N, 'A', 'C', 'B');
      assert(moves_counter == num_moves(t1,N));
    }
    if(t1==2) {
      sposta_torre_with_all_moves(N, 'A', 'C', 'B');
      assert(moves_counter == num_moves(t1,N));
    }
  }
  return 0;
}

