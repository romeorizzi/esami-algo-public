/**
 *  File: sol_slow.cpp
 *  Soluzione di hanoi_equal_disks (lenta nel conteggio, per simulazione)
 *
 *  Romeo Rizzi, 2018-09-21
 *
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;
//const int DEBUG = 1;
const int MAXN = 100000;

int t, N, moves_done = 0;
int d[MAXN+1];
char pole[MAXN+1];


void sposta_disco(int n, char piolo_from, char piolo_to) {
  assert(pole[n]==piolo_from);
  printf("sposta il disco %d dal piolo %c al piolo %c\n", n, piolo_from, piolo_to);
  pole[n] = piolo_to;
}

void conta_spostamenti_disco(int n, char piolo_from, char piolo_to) {
  assert(pole[n]==piolo_from);
  moves_done++;
  pole[n] = piolo_to;
}  

void sposta_torre(int n, char piolo_from, char piolo_to, char piolo_aux, void (*basicActionOnDisk) (int,char,char) ) {
  if(n == 0) return;
  int nn = n;
  while(nn > 1 && d[nn] == d[nn-1])
    nn--;
  sposta_torre(nn-1, piolo_from, piolo_aux, piolo_to, basicActionOnDisk);
  for(int i=nn; i <= n; i++)
    (*basicActionOnDisk)(i, piolo_from, piolo_to);
  sposta_torre(nn-1, piolo_aux, piolo_to, piolo_from, basicActionOnDisk);
}


int main() {
  scanf("%d%d", &t, &N);
  for(int i = 1; i <= N; i++) {
    scanf("%d", &d[i]);
    pole[i] = 'A';
  }
  if(t==0) {
    sposta_torre(N, 'A', 'B', 'C', &conta_spostamenti_disco);
    printf("%d\n", moves_done);
  }  
  else sposta_torre(N, 'A', 'B', 'C', &sposta_disco);
        
  return 0;
}

