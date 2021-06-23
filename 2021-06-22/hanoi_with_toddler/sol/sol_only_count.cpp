/**
 *  File: soluzione.cpp
 *  Soluzione parziale di hanoi_with_toddler (solo casi di tipo t=0, ossia non specifica le mosse ma si limita a contarle)
 *
 *  Autore: Romeo Rizzi, 2021-06-20
 *
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;
//const int DEBUG = 1;
const int MAXN = 100000;

typedef long long unsigned int llu;

int t, N;
char curr_peg[MAXN +1], dest_peg[MAXN +1];

// implementiamo una simulazione parziale per un processo ibrido che si permette la macro di spostare intere torri di N' dischi con N'<N. Questo stile descrittivo-ibrido offre già una visualizzazione e quindi opportunità di debugging
void sposta_disco(int n, char peg_from, char peg_to) {
  assert(curr_peg[n]==peg_from);
  if(DEBUG) printf("meta-spostamento del disco %d dal piolo %c al piolo %c\n", n, peg_from, peg_to);
  curr_peg[n] = peg_to;
}

llu num_moves(int n) {
  if(n==0)
    return 0;
  else
    return 2*num_moves(n-1) +1;
}

void display_peg(char *peg) { // good for debugging
  for(int i = 1; i <= N; i++)
    printf("%c ", peg[i]);
    printf("\n");
}

char third_peg(char peg1, char peg2) {
  return 'A'+ (3 - (peg1-'A') - (peg2-'A') );
}

int main() {
  scanf("%d%d", &t, &N);
  for(int i = 1; i <= N; i++) {
    curr_peg[i] = 'A';
    do {
      scanf("%c", &dest_peg[i]);
    } while(dest_peg[i] != 'A' && dest_peg[i] != 'B' && dest_peg[i] != 'C');
  }
  llu smart_numMoves = 0;
  for(int next_disk_to_fix = N; next_disk_to_fix > 0; next_disk_to_fix--)
    if(curr_peg[next_disk_to_fix] != dest_peg[next_disk_to_fix]) {
      if(DEBUG) {printf("Current situation:\n   "); display_peg(curr_peg);}
      if(DEBUG) {printf("Desired situation:\n   "); display_peg(dest_peg);}
      smart_numMoves += num_moves(next_disk_to_fix-1) +1;
      char aux_peg = third_peg(curr_peg[next_disk_to_fix], dest_peg[next_disk_to_fix]);
      for(int i = next_disk_to_fix-1; i > 0; i--)
	sposta_disco(i, curr_peg[i], aux_peg);
      sposta_disco(next_disk_to_fix, curr_peg[next_disk_to_fix], dest_peg[next_disk_to_fix]);
    }
        
  if(DEBUG) {printf("Current situation:\n   "); display_peg(curr_peg);}
  if(DEBUG) {printf("Desired situation:\n   "); display_peg(dest_peg);}
  for(int i = 1; i <= N; i++)  assert(curr_peg[i] == dest_peg[i]);

  printf("%llu\n", smart_numMoves);
  if(t>0)
    printf("Sò che avrei dovuto elencare le mosse ma ho preferito limitarmi a contarle.");
  
  return 0;
}

