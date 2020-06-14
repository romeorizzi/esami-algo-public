/**
 *  online_budget
 *
 *  Autore: Romeo Rizzi, 2019-07-28
 *
 *  Costo di questa soluzione: esponenziale, traccia ogni singola history.
 *
 *  Descrizione: ricorsione elementare.
 */

#include <assert.h>
#include <stdio.h>

#define MAX_N 500
#define MAX_VAL 10
#define BIG_PRIME 1000000007
  
int n, B0, x[MAX_N];

void print_array(int *v, int len) {
  for(int i = 0; i < len; i++)
      printf("%d ", v[i]);
  printf("\n");
}

long int risp[MAX_N+1][MAX_VAL*MAX_N + 1001];

long int num_histories_from(int i, int B) {
  //cout << "Call with i = " << i << " and B = " << B << "Here, risp[i][B] = " << risp[i][B] << endl;
  if(risp[i][B] == -1) {
    if(i == n)
      risp[i][B] = 1;
    else {
      risp[i][B] = 0;
      for(int spesa_i = 0; spesa_i <= B; spesa_i++)
        risp[i][B] = (risp[i][B] + num_histories_from(i+1, B -spesa_i +x[i] ) ) % BIG_PRIME;
  }
  return risp[i][B];
}

int main() {
    scanf("%d %d", &n, &B0);
    for(int i = 0; i < n; i++)
       scanf("%d", &x[i]);
    //print_array(x, n);

    for(int i = 0; i <= n; i++)
      for(int b = 0; b <= MAX_VAL*n + B0; b++)
        risp[i][b] = -1;
    
    printf("%ld\n", num_histories_from(0,B0));
    return 0;
}

