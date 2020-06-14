/**
 *  Soluzione di easyfall
 *
 *  Autore: Romeo Rizzi, 2017-09-25
 *
 *  Costo di questa soluzione: lineare, ottima.
 *
 *  Descrizione: se la caduta di una tessera i comporta la caduta di una tessera successiva j>i allora la scelta di usare una pallina sulla tessera i domina quella di usarla sulla tessera j. A causa di cio` emerge una struttura ad isole, che partizionano in intervalli la sequenza delle tessere, ciascuna isola e` interamente abbattibile colpendo la sua tessera piu` a sinistra, e qualunque tessera venga abbattuta entro un'isola non potra` avere influsso su tessere nelle altre isole. A valle della comprensione di questa struttura, si chiarisce che conviene abbattare prima le isole grosse e poi via via quelle piu` piccole, seguendo una politica greedy.
 */

#include <cassert>
#include <cstdio>

#define MAXN 1000000

int N;
int h[MAXN+1]; // altezze delle tessere
int count[MAXN+1]; // count[i] = numero di isole con i tessere

int mymax(int a, int b) { return (a>b) ? a : b; }

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
       scanf("%d", &h[i]);

    int i = 1; int nIsola = 1;
    while( i <= N ) {
        int len = 1; // lunghezza dell'isola corrente
	int goes_to_at_least = i+h[i]-1; // lower-bound su estremo destro dell'isola corrente
        while( (i < N) && (i < goes_to_at_least) ) {
	  i++; len++;
	  goes_to_at_least = mymax(goes_to_at_least, i+h[i]-1);
          //printf("i = %d, nIsola = %d, len = %d\n", i, nIsola, len);
	}
	assert( (i == N) || (i == goes_to_at_least) );
	count[len]++;
	i++; nIsola++;
    }

    int killed = 0;
    for(int len = N; len > 0; len--)
      while( count[len]-- ) {
	killed += len;
        printf("%d ", killed);
      }
    while(nIsola++ <= N)
       printf("%d ", killed);	 
    printf("\n");
    
    return 0;
}

