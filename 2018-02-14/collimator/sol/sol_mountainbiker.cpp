/**
 *  Soluzione parziale di collimator
 *
 *  Autore: Romeo Rizzi, 2018-02-10
 *
 *  Costo di questa soluzione: lineare, ma risolve correttamente solo alcuni dei subtask.
 *
 *  Tecnica: di fatto risolviamo un altro problema piu` semplice, quello di trovare una scrittura del vettore rad con moltiplicatori lambda ma minimizzando la somma dei landa invece che non il numero dei lambda non nulli.
 *  Le soluzioni ottime dei due problemi coincidono quando |vec[i]-vec[j]| <= |i-j| ossia quando la differenza tra ogni numero ed il suo successivo non eccede mai 1.
 * 
 *  Idea/metafora della soluzione: noi vediamo i numeri come delle altitudini di un profilo montano. Un hiker in mountainbike percorre il profilo montano da sinistra verso destra. Ogni volta che sale paga il dislivello, ma le discese sono invece gratis (adrenalina pura).
 *  Dettaglio: rimane comodo l'impiego di valori sentinella (settare rad[0]=0=rad[n+1]) per assumere che il primissimo ed ultimissimo valore siano nulli.
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
       if( delta > 0 ) risp += delta;
    }

    printf("%d\n", risp);
    
    return 0;
}

