/**
 *  Soluzione di collimator
 *
 *  Autore: Romeo Rizzi, 2018-02-10
 *
 *  Costo di questa soluzione: lineare, ottima.
 *
 *  Tecnica: utilizzo di uno stack per spianare le cime
 * 
 *  Descrizione: tramite l'eventuale uso di sentinelle (settando rad[0]=0=rad[n+1]), possiamo assumere che il primissimo ed ultimissimo valore siano nulli. Si legge da sinistra verso destra annotandosi in uno stack i delta positivi (salti in su` nel procedere da sinistra verso destra). Quando ci si trova a gestire un delta negativo, esso viene gestito per elisione con quanto nello stack. Ogni valore eliso dallo stack comporta un unita` di aggravio in termini di valore della funzione obiettivo (risp).
 */

#include <cassert>
#include <cstdio>

#define MAXN 1000000

int n;

int stack[MAXN+1]; int posW = 0;

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d", &n);
    int risp = 0;
    int prev_h = 0, new_h;
    for(int i = 1; i <= n+1; i++) {
       if(i <= n)
          scanf("%d", &new_h);
       else new_h = 0;
       // printf("+ new_h = %d\n", new_h);
       int delta = new_h - prev_h;
       // printf("   --> delta = %d\n", delta);
       prev_h = new_h;
       if( delta > 0 ) stack[posW++] = delta;
       if( delta < 0 ) {
	 int drop = -delta; assert( drop > 0 );
	 while( (drop > 0) && drop>=stack[posW -1]) {
	   drop -= stack[posW-1];
	   stack[posW-1] = 0;
	   posW--;
	   risp++;
	 }    
	 assert( posW >= 0 );
	 assert( drop >= 0 );
	 if(drop > 0) {
    	    assert( posW > 0 );   
	    stack[posW-1] -= drop;
    	    assert( stack[posW-1] > 0 );
	    risp++;
	 }   
       }
    }
    assert(posW == 0);

    printf("%d\n", risp);
    
    return 0;
}

