/**
 *  is_shuffle_of
 *
 *  Autore: Romeo Rizzi, 2019-06-25
 *
 *  Costo di questa soluzione: quadratico.
 *
 *  Descrizione: programmazione dinamica. Decide solo se w sia uno shuffle possibili di x ed y, non ricostruisce una soluzione/certificato.
 */

#include <cassert>
#include <cstdio>
#include <algorithm>

#define MAXM 1000
#define MAXN 1000

int m, n, output_type;
int x[MAXM+1], y[MAXN+1], w[MAXM + MAXN+1]; // we prefer to index the sequences starting from 1.
int shuffle_into_w_prefix[MAXM+1][MAXN+1];
/*
 The matrix shuffle_into_w_prefix  is the matrix of the dynamic programming problems.
 We denote by s_i the prefix of the first i charcters of a string s. Then these mxn problems are the following:
 shuffle_into_w_prefix[i][j] = 1 of w_{i+j} is a shuffle of x_i and y_j
                             = 0 otherwise.
 */

void print_array(int *v, int len) {
  for(int i = 0; i < len; i++)
      printf("%d ", v[i]);
  printf("\n");
}

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d %d %d", &m, &n, &output_type);
    for(int i = 1; i <= m; i++)
       scanf("%d", &x[i]);
    for(int i = 1; i <= n; i++)
       scanf("%d", &y[i]);
    for(int i = 1; i <= m+n; i++)
       scanf("%d", &w[i]);
    //printf("x= "); print_array(x, m+1);
    //printf("y= "); print_array(y, n+1);
    //printf("w= "); print_array(w, m+n+1);

    shuffle_into_w_prefix[0][0] = 1;
    
    for(int i = 1; i <= m; i++)
        if(x[i] == w[i] && shuffle_into_w_prefix[i-1][0])
          shuffle_into_w_prefix[i][0] = 1;
    for(int j = 1; j <= n; j++)
        if(y[j] == w[j] && shuffle_into_w_prefix[0][j-1])
          shuffle_into_w_prefix[0][j] = 1;
      
    for(int i = 1; i <= m; i++)
      for(int j = 1; j <= n; j++) {
        if(x[i] == w[i+j] && shuffle_into_w_prefix[i-1][j] )
          shuffle_into_w_prefix[i][j] = 1;
        if(y[j] == w[i+j] && shuffle_into_w_prefix[i][j-1] )
          shuffle_into_w_prefix[i][j] = 1;
	//printf("i=%d, j=%d, P[i,j]=%d\n", i,j,shuffle_into_w_prefix[i][j]);
      }  
    printf("%d\n", shuffle_into_w_prefix[m][n]);

    /*for(int i = 0; i <= m; i++) {
      for(int j = 0; j <= n; j++)
        printf("%d ", shuffle_into_w_prefix[i][j]);
      printf("\n");
      }*/  

    return 0;
}

