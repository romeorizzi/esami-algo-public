/**
 *  File: soluzione.cpp
 *  Soluzione di hanoi_clockwise
 *  Romeo Rizzi, 2020-02-18
 *
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;
//const int DEBUG = 1;
const int MAXN = 100000;

typedef long long unsigned int llu;

int t, N;
char peg[MAXN+1];
char d[MAXN+1];
llu memo_num2[MAXN+1];

void sposta_disco(int n, char peg_from, char peg_to) {
  assert(peg[n]==peg_from);
  printf("sposta il disco %d dal peg %c al peg %c\n", n, peg_from, peg_to);
  peg[n] = peg_to;
}

char next_peg(char peg) {
  if(peg == 'A') return 'B';
  if(peg == 'B') return 'C';
  if(peg == 'C') return 'A';
}

void sposta_intera_torre(int n, char peg_from, char peg_to, char peg_aux) {
  //assume che tutti i dischi i <= n siano uno sopra l'altro in torre sul peg <peg_from>.
  //Sposta questa intera torre sul peg <peg_to>, impiegano il minor numero di mosse possibile.
  //Si assume che <peg_aux> indichi il terzo peg."""
  if(DEBUG) {
    printf("called sposta_intera_torre(n=%d, peg_from=%c, peg_to=%c, peg_aux=%c)\n", n, peg_from, peg_to, peg_aux);
  }
  if(n == 0) return;
  if(peg_to == next_peg(peg_from)) {
    sposta_intera_torre(n-1, peg_from, peg_aux, peg_to);
    sposta_disco(n, peg_from, peg_to);
    sposta_intera_torre(n-1, peg_aux, peg_to, peg_from);
  }  else {
    sposta_intera_torre(n-1, peg_from, peg_to, peg_aux);
    sposta_disco(n, peg_from, peg_aux);
    sposta_intera_torre(n-1, peg_to, peg_from, peg_aux);
    sposta_disco(n, peg_aux, peg_to);
    sposta_intera_torre(n-1, peg_from, peg_to, peg_aux);
  }
}

llu num_steps_sposta_intera_torre_by_2(int n);

llu num_steps_sposta_intera_torre_by_1(int n) { 
  //ritorna il numero di passi per spostare un'intera torre quando peg_to == next_peg(peg_from)
  if(n == 0) return 0;
  return 1 + 2*num_steps_sposta_intera_torre_by_2(n-1);
}

llu num_steps_sposta_intera_torre_by_2(int n) { 
  //ritorna il numero di passi per spostare un'intera torre quando peg_to == next_peg(next_peg(peg_from))
  if(n==0) return 0;
  if(memo_num2[n] == 0)
    memo_num2[n] = 2 + 2*num_steps_sposta_intera_torre_by_2(n-1) + num_steps_sposta_intera_torre_by_1(n-1);
  return memo_num2[n];
}

void smista_torre(int n) {
  //assume che tutti i dischi i <= n siano uno sopra l'altro in torre, tutti collocati su peg[n].
  //Li consegna tutti alla loro destinazioni finali, come indicate in d.
  if(n == 0) return;
  if(peg[n] == d[n]) {
    smista_torre(n-1);
    return;
  }
  sposta_intera_torre(n-1, peg[n-1], next_peg(next_peg(peg[n])), next_peg(peg[n]));
  sposta_disco(n, peg[n], next_peg(peg[n]));
  if(peg[n] == d[n]) {
      smista_torre(n-1);
      return;
  }
  sposta_intera_torre(n-1, peg[n-1], next_peg(peg[n-1]), next_peg(next_peg(peg[n-1])));
  sposta_disco(n, peg[n], d[n]);
  smista_torre(n-1);
}
    
llu num_steps_smista_torre(int n) {
  //Assume che tutti i dischi i <= n siano uno sopra l'altro in torre, tutti collocati su peg[n].
  //Ritorna il numero di passi per smistare ciascun disco i <= n come specificato dalla destinazione d[i]""" 
  if(n == 0) return 0;
  if(peg[n] == d[n])
    return num_steps_smista_torre(n-1);
  llu risp = 1 + num_steps_sposta_intera_torre_by_2(n-1);
  if(next_peg(peg[n]) != d[n])
    risp += 1 + num_steps_sposta_intera_torre_by_1(n-1);
  peg[n] = d[n];
  for(int i = 1; i<n; i++)
    peg[i] = next_peg(peg[n]);
  return risp + num_steps_smista_torre(n-1);
}

int main() {
  scanf("%d%d", &t, &N);
  bool allB_final_conf = true;
  for(int i = 1; i <= N; i++) {
    peg[i] = 'A';
    do {
      scanf("%c", &d[i]);
    } while(d[i] != 'A' && d[i] != 'B' && d[i] != 'C');
    if(d[i] != 'B') allB_final_conf = false;
  }
  if(t==0)
    printf("%llu\n", num_steps_smista_torre(N));
  else {
    if(allB_final_conf) {
      sposta_intera_torre(N, 'A', 'B', 'C');
    }
    else{
      smista_torre(N);
    }
  }
        
  return 0;
}

