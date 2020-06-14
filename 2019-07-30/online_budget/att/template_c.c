/**
 *  Template per soluzione in c per il problema online_budget
 *
 *  Romeo Rizzi, 2019-07-28
 *
 */

#include <assert.h>
#include <stdio.h>

#define MAX_N 500
#define MAX_VAL 10

int n, B0, x[MAX_N];

void print_array(int *v, int len) {
  for(int i = 0; i < len; i++)
      printf("%d ", v[i]);
  printf("\n");
}

int main() {
    scanf("%d %d", &n, &B0);
    for(int i = 0; i < n; i++)
       scanf("%d", &x[i]);
    //print_array(x, n);

    long int risp = 42;

    printf("%ld\n", risp);
    return 0;
}

