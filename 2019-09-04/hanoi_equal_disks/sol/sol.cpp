/**
 *  File: soluzione.cpp
 *  Soluzione di hanoi_equal_disks
 *  Romeo Rizzi, 2019-08-28
 *
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;
//const int DEBUG = 1;
const int MAXN = 100000;

int t, N;
int d[MAXN+1];
char pole[MAXN+1];

typedef long long unsigned int llu;

llu num_steps() {
  llu n_steps = 0;
  llu n_moves_per_disk = 1;
  for(int i = N; i > 0; i--) {
    n_steps += n_moves_per_disk;
    if(DEBUG)
      fprintf(stderr,"i=%d, n_moves_per_disk = %llu",i,n_moves_per_disk);
    if(i > 1 && d[i] > d[i-1])
      n_moves_per_disk *= 2;
  }
  return n_steps;
}

void sposta_disco(int n, char piolo_from, char piolo_to) {
  assert(pole[n]==piolo_from);
  printf("sposta il disco %d dal piolo %c al piolo %c\n", n, piolo_from, piolo_to);
  pole[n] = piolo_to;
}

void sposta_torre(int n, char piolo_from, char piolo_to, char piolo_aux) {
  if(n == 0) return;
  int nn = n;
  while(nn > 1 && d[nn] == d[nn-1])
    nn--;
  sposta_torre(nn-1, piolo_from, piolo_aux, piolo_to);
  for(int i=nn; i <= n; i++)
    sposta_disco(i, piolo_from, piolo_to);
  sposta_torre(nn-1, piolo_aux, piolo_to, piolo_from);
}


int main() {
  scanf("%d%d", &t, &N);
  for(int i = 1; i <= N; i++) {
    scanf("%d", &d[i]);
    pole[i] = 'A';
  }
  if(t==0)
    printf("%llu\n", num_steps());
  else
    sposta_torre(N, 'A', 'B', 'C');
        
  return 0;
}

