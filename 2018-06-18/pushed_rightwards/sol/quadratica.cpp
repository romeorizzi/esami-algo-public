/**
 *  pushed_rightwards
 *  soluzione di DP quadratica
 *
 *  Autore: Romeo Rizzi, 2018-06-18
 *
 *  Costo di questa soluzione: lineare.
 *
 *  Descrizione: programmazione dinamica.
 */

#include <cassert>
#include <cstdio>
#include <algorithm>

#define MAXN 1000000

int N;
int g[MAXN]; // g[i] = numero celle in cella i-esima.
int t[MAXN]; // t[i] = troll treathening in cella i-esima.

int max_sum_g[MAXN];

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
       scanf("%d", &g[i]);
    for(int i = 0; i < N; i++)
       scanf("%d", &t[i]);
    
    for(int i = N-1; i >= 0; i--) {
      max_sum_g[i] = g[i];
      for(int ii = i + t[i] +1; ii < N; ii++)
	if(max_sum_g[i] < g[i] + max_sum_g[ii])
          max_sum_g[i] = g[i] + max_sum_g[ii];
    }  
    printf("%d\n", max_sum_g[0]);
    
    return 0;
}

