/**
 * Un template per la tua soluzione di hanoi_split
 * Romeo Rizzi, 2021-07-20
 *
 */

#include <cassert>
#include <cstdio>

//const int DEBUG = 0;
const int DEBUG = 1;

typedef long long unsigned int llu;

int t, N;

// implemento prima la simulazione (più facile, mi abbandono agli stili descrittivo e ricorsivo)
void sposta_disco(int n, char peg_from, char peg_to) {
  printf("sposta il disco %d dal piolo %c al piolo %c\n", n, peg_from, peg_to);
}


int main() {
  scanf("%d%d", &t, &N);
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
