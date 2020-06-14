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

long int num_histories_from(int i, int B) {
  if(i == n)
    return 1;
  long int risp = 0;
  for(int spesa_i = 0; spesa_i <= B; spesa_i++)
    risp = (risp + num_histories_from(i+1, B -spesa_i +x[i] ) ) % BIG_PRIME;
  return risp;
}

int main() {
    scanf("%d %d", &n, &B0);
    for(int i = 0; i < n; i++)
       scanf("%d", &x[i]);
    //print_array(x, n);

    printf("%ld\n", num_histories_from(0,B0));
    return 0;
}

