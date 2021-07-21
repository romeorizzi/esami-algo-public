/**
 *  File: sol.cpp
 *  Soluzione di riferimento per poldo_game, quadratica nel tempo e lineare nello spazio
 *
 *  Autore: Romeo Rizzi, 2021-07-20
 *
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;
//const int DEBUG = 1;
const int MAXN = 200;

typedef long long unsigned int llu;

int N;
int colesterolo[MAXN+1]; // I panini (portate) sono numerati partendo da 0. Sugli indici pari sceglie Poldo cui spetta scegliere ad esempio sulla prima portata. Viene però comodo un (N+1)-esimo panino fittizio con questo valore di colesterolo colesterolo[N]=0.
int P[MAXN+1][MAXN+1]; /* P[i][j] = numero di portate che verrebbero infine assaggiate se fossero interdette tutte le portate con valore di colesterolo <= colesterolo[j] e tutte le portate che precedono l'i-esima.
Note: I panini (portate) sono numerati partendo da 0. Il primo a scegliere resta determinato da i%2 secondo la regola che sugli indici pari sceglie Poldo, cui ad esempio spetta di scegliere sulla prima portata.*/

inline int my_min(int a, int b) { return (a<b) ? a : b; }
inline int my_max(int a, int b) { return (a>b) ? a : b; }

int main() {
  scanf("%d", &N);
  for(int i = 0; i < N; i++)
    scanf("%d", &colesterolo[i]);
  for(int i=N-1; i >= 0; i--) {
    for(int j=0; j<=N; j++) {
      int P_i_se_non_mangio_i = P[i+1][j];
      if(colesterolo[i] <= colesterolo[j])
	P[i][j] = P_i_se_non_mangio_i;
      else {      
	int P_i_se_mangio_i = 1 + P[i+1][i];
        if(i%2==0)  //sceglie poldo
	  P[i][j] = my_max(P_i_se_mangio_i, P_i_se_non_mangio_i);
        if(i%2==1)  //sceglie il dottore
	  P[i][j] = my_min(P_i_se_mangio_i, P_i_se_non_mangio_i);    
      }
    }
  }
  printf("%d\n", P[0][N]);
        
  if(DEBUG) {
    for(int i = 0; i < N; i++)
      printf("%d ", P[i][N]);
    printf("\n");
  }
  return 0;
}

