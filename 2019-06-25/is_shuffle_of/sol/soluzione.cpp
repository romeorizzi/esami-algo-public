/**
 *  is_shuffle_of
 *
 *  Autore: Romeo Rizzi, 2019-06-25
 *
 *  Costo di questa soluzione: quadratico.
 *
 *  Descrizione: programmazione dinamica.
 */

#include <cassert>
#include <cstdio>
#include <algorithm>

#define MAXM 1000
#define MAXN 1000

int m, n, output_type;
int x[MAXM+1], y[MAXN+1], w[MAXM + MAXN+1]; // we prefer to index the sequences starting from 1. Also: in this solution we prefer to index the strings reversed, so that working with the suffixes of a given length gets natural.
int shuffle_into_w_suffix[MAXM+1][MAXN+1];
int take_x_on_w[MAXM + MAXN+1]; // to store the solution/certificate. For coherence, still we prefer to index the sequences starting from 1 but now we go forward.
/*
 The matrix shuffle_into_w_suffix  is the matrix of the dynamic programming problems.
 We denote by s^i the suffix of the first i characters of a string s. Then these mxn problems are the following:
 shuffle_into_w_suffix[i][j] = 1 of w^{i+j} is a shuffle of x^i and y^j
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
    for(int i = 0; i < m; i++)
       scanf("%d", &x[m-i]);
    for(int i = 0; i < n; i++)
       scanf("%d", &y[n-i]);
    for(int i = 0; i < m+n; i++)
       scanf("%d", &w[m+n-i]);
    //printf("x= "); print_array(x, m+1);
    //printf("y= "); print_array(y, n+1);
    //printf("w= "); print_array(w, m+n+1);

    shuffle_into_w_suffix[0][0] = 1;
    
    for(int i = 1; i <= m; i++)
        if(x[i] == w[i] && shuffle_into_w_suffix[i-1][0])
          shuffle_into_w_suffix[i][0] = 1;
    for(int j = 1; j <= n; j++)
        if(y[j] == w[j] && shuffle_into_w_suffix[0][j-1])
          shuffle_into_w_suffix[0][j] = 1;
      
    for(int i = 1; i <= m; i++)
      for(int j = 1; j <= n; j++) {
        if(x[i] == w[i+j] && shuffle_into_w_suffix[i-1][j] )
          shuffle_into_w_suffix[i][j] = 1;
        if(y[j] == w[i+j] && shuffle_into_w_suffix[i][j-1] )
          shuffle_into_w_suffix[i][j] = 1;
	//printf("i=%d, j=%d, P[i,j]=%d\n", i,j,shuffle_into_w_prefix[i][j]);
      }  
    printf("%d\n", shuffle_into_w_suffix[m][n]);

    if(shuffle_into_w_suffix[m][n] && output_type) {
      int len_good_x_suffix = m;
      int len_good_y_suffix = n;
      while(len_good_x_suffix + len_good_y_suffix > 0)
	if(len_good_x_suffix > 0 && x[len_good_x_suffix] == w[len_good_x_suffix + len_good_y_suffix] && shuffle_into_w_suffix[len_good_x_suffix-1][len_good_y_suffix]) {
	  take_x_on_w[m+n+1 -len_good_x_suffix - len_good_y_suffix] = 0;
	  len_good_x_suffix--;
	}
        else {
	  assert(len_good_y_suffix > 0 && y[len_good_y_suffix] == w[len_good_x_suffix + len_good_y_suffix] && shuffle_into_w_suffix[len_good_x_suffix][len_good_y_suffix-1]);
	  take_x_on_w[m+n+1 -len_good_x_suffix - len_good_y_suffix] = 1;
	  len_good_y_suffix--;
	}
      for(int i = 1; i <= m+n; i++)
	printf("%d ", take_x_on_w[i]);
      printf("\n");
    }

    /*for(int i = 0; i <= m; i++) {
      for(int j = 0; j <= n; j++)
        printf("%d ", shuffle_into_w_prefix[i][j]);
      printf("\n");
      }*/  


    return 0;
}

