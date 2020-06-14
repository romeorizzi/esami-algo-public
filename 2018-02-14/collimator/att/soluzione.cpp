/**
 *  Soluzione farlocca di collimator
 *
 *  Autore: Romeo Rizzi, 2018-02-10
 *
 *  Scopo: fornire bozza da cui partire con incluse primitive per input ed output
 * 
 */


#include <cassert>
#include <cstdio>

#define MAXN 1000000

int n;

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
       int new_h;
       scanf("%d", &new_h);
       printf("+ new_h = %d\n", new_h);
    }

    printf("%d\n", 0); //risposta corretta solo quando il vettore in input e` identicamente nullo.
    
    return 0;
}

