/**
 *  Soluzione farlocca di pushed_rightwards (illustra come curare input ed output)
 *
 *  Autore: Romeo Rizzi, 2018-06-18
 *
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
    
    printf("%d\n", 0); // giusto ad esempio quando non ci sono gemme 
    
    return 0;
}

