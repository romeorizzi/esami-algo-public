/**
 *  File: sol.cpp
 *  Soluzione per incr_subseq_with_drops, quadratica nel tempo e lineare nello spazio
 *  Romeo Rizzi, 2022-07-23
 *
 */

#include <cassert>
#include <cstdio>

const int MAXN = 200;
const int MAXK = 200;
const int MOD=1000000007;

typedef long long unsigned int llu;

int g,N,K;
int s[MAXN]; // Gli indici della sequenza in input partono da 0.
int max_from[MAXK+1][MAXN+1]; // max_from[k][i] = massima lunghezza di una sottosequenza di al più k drops che abbia s[i] come suo primo elemento (se i=n la lunghezza è 0)
int num_opts_from[MAXK+1][MAXN+1]; // num_opts_from[k][i] = numero di sottosequenze di al più k drops che abbiano s[i] come loro primo elemento aventi massima lunghezza (se i=n tale numero è 1 e corrisponde alla sequenza vuota)

int main() {
  scanf("%d %d %d", &g, &N, &K);
  for(int i = 0; i < N; i++)
    scanf("%d", &s[i]);
  for(int k=0; k<=MAXK; k++) num_opts_from[k][N] = 1;
  for(int i=N-1; i >= 0; i--) {
    for(int k=0; k<=MAXK; k++) {
      max_from[k][i] = 0;
      num_opts_from[k][i]=1;
      for(int j=N-1; j>i; j--) {
        if(s[j]>s[i]) { //s_j candida per essere il prossimo elemento della sottosequenza senza incremento in drops
          if(1+max_from[k][j]>max_from[k][i]) {
  	      max_from[k][i] = 1+max_from[k][j];
              num_opts_from[k][i] = num_opts_from[k][j];
	  }
          else if(1+max_from[k][j]==max_from[k][i]) {
	    num_opts_from[k][i] = (num_opts_from[k][i] + num_opts_from[k][j]) % MOD;
	  }
	}
	else if(k>0) {
          if(1+max_from[k-1][j]>max_from[k][i]) {
  	      max_from[k][i] = 1+max_from[k-1][j];
              num_opts_from[k][i] = num_opts_from[k-1][j];
	  }
          else if(1+max_from[k-1][j]==max_from[k][i]) {
              num_opts_from[k][i] = (num_opts_from[k][i] + num_opts_from[k-1][j]) % MOD;
	  }
	}
      }
    }
  }
  if(g==1)
    printf("%d\n", max_from[K][0]);
  else if(g==2)
    printf("%d\n", num_opts_from[K][0]);
  else
    assert(0);
        
  return 0;
}

