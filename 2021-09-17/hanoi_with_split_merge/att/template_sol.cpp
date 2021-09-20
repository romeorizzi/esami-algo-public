/**
 * Un template per la tua soluzione di hanoi_with_split_merge
 * Romeo Rizzi, 2021-09-17
 *
 */

#include <cassert>
#include <cstdio>

//const int DEBUG = 0;
const int DEBUG = 1;

typedef long long unsigned int llu;

int t, t1, N;

// implemento prima la simulazione (più facile, mi abbandono agli stili descrittivo e ricorsivo)
void sposta_disco(int n, char peg_from, char peg_to) {
  printf("sposta il disco %d dal piolo %c al piolo %c\n", n, peg_from, peg_to);
}

void split_dal_disco(int i, char peg_from, char peg_dest1, char peg_dest2) {
  printf("split il piolo %c, dal disco %d, sui pioli %c e %c\n", peg_from,i,peg_dest1,peg_dest2);
}

void merge_dal_disco(int i, char peg_dest, char peg_from1, char peg_from2) {
  printf("merge sul piolo %c, dal disco %d del piolo %c e dal piolo %c\n", peg_dest,i,peg_from1,peg_from2);
}

int main() {
  scanf("%d%d%d", &t, &t1, &N);
  if(t==0)
    printf("%llu\n", 42); // TO DO: stampa il numero di mosse
  else {
    // TO DO (il template si limita a fornire la lista esplicita di mosse per N=3. A tè introdurre le procedure con la giusta logica in questo file
    sposta_disco(1,'A','B');
    sposta_disco(2,'A','C');
    sposta_disco(1,'B','C');
    sposta_disco(3,'A','B');
    sposta_disco(1,'C','B');
  }
        
  return 0;
}
