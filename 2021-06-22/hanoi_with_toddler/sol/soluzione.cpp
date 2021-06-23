/**
 *  File: soluzione.cpp
 *  Soluzione di hanoi_with_toddler
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
llu numMoves = 0;

char player_name[2][10] = {"daddy ", "toddler "};
int player = 0;

// implemento prima la simulazione (più facile, mi abbandono agli stili descrittivo e ricorsivo)
void sposta_disco(int n, char peg_from, char peg_to) {
  assert(curr_peg[n]==peg_from);
  printf("%smuove il disco %d dal piolo %c al piolo %c\n", player_name[player], n, peg_from, peg_to);
  curr_peg[n] = peg_to;
  numMoves += 1;
  player = 1-player;
}

void sposta_intera_torre(int n, char peg_from, char peg_to, char peg_third) {
  if(DEBUG) printf("CALLED: sposta_intera_torre(n=%d, peg_from=%c, peg_to=%c, peg_third=%c)\n", n, peg_from, peg_to, peg_third);
  assert(n==0 || curr_peg[n]==peg_from);
  if(n==0 || peg_from==peg_to)
    return;
  else {
    sposta_intera_torre(n-1, peg_from, peg_third, peg_to);
    sposta_disco(n, peg_from, peg_to);
    sposta_intera_torre(n-1, peg_third, peg_to, peg_from);
  }
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
      if(t==1) {
        sposta_intera_torre(next_disk_to_fix-1, curr_peg[next_disk_to_fix], aux_peg, dest_peg[next_disk_to_fix]);
        sposta_disco(next_disk_to_fix, curr_peg[next_disk_to_fix], dest_peg[next_disk_to_fix]);
	assert(numMoves==smart_numMoves);
      }
      else {
	for(int i = next_disk_to_fix-1; i > 0; i--)
	  curr_peg[i] = aux_peg;
	curr_peg[next_disk_to_fix] = dest_peg[next_disk_to_fix];
      }
    }
  if(t==0)
    printf("%llu\n", smart_numMoves);
        
  if(DEBUG) {printf("Current situation:\n   "); display_peg(curr_peg);}
  if(DEBUG) {printf("Desired situation:\n   "); display_peg(dest_peg);}
  for(int i = 1; i <= N; i++)  assert(curr_peg[i] == dest_peg[i]);

  return 0;
}

