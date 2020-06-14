/**
 *  Soluzione test di collimator
 *
 *  Autore: Romeo Rizzi, 2018-02-10
 *
 *  Costo di questa soluzione: quadratica.
 *
 *  Descrizione: utilizzare l'intervallo totale (quello da estrema sinistra ad estrema destre) fino all'altezza del minimo valore (questo costa 1 se il minimo e` maggiore di 0, e costa 0 altrimenti). Poi il problema si spezza dove il livello dell'acqua ha raggiunto il minimo. Posso pertanto procedere ricorsivamente.
Alle chiamate ricorsive passo gli estremi del sottointervallo ed il livello gia` raggiunto dall'acqua.
 */

#include <cassert>
#include <cstdio>

#define MAXN 1000000

int n;

int vec[MAXN];

int ric(int left, int right, int water) {
  if(right < left) return 0;
  int my_cost = 0;
  int pos_min = left;
  for(int i = left+1; i <= right; i++)
     if(vec[i] < vec[pos_min])
	pos_min = i;
  assert( vec[pos_min] >= water );
  if( vec[pos_min] > water ) {
    my_cost = 1;
    water = vec[pos_min];
  }
  my_cost += ric(left, pos_min-1, water);
  my_cost += ric(pos_min+1, right, water);
  return my_cost;
}  

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
       scanf("%d", &vec[i]);

    printf("%d\n", ric(0,n-1,0));
    
    return 0;
}

