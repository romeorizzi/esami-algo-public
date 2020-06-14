/**
 *  Template per soluzione in c per il problema online_budget_opt
 *
 *  Romeo Rizzi, 2019-07-28
 *
 */

#include <assert.h>
#include <stdio.h>

#define MAX_N 1000000
#define MAX_VAL 10

int n, B0, output_type, x[MAX_N], q[MAX_N], is_index_of_last_opportunity[MAX_N];
long int y[MAX_N];

void print_array(int *v, int len) {
  for(int i = 0; i < len; i++)
      printf("%d ", v[i]);
  printf("\n");
}

int main() {
    scanf("%d %d %d", &n, &B0, &output_type);
    for(int i = 0; i < n; i++)
       scanf("%d", &x[i]);
    for(int i = 0; i < n; i++)
       scanf("%d", &q[i]);
    //print_array(x, n);
    //print_array(q, n);

    y[0] = B0;
    for(int i = 1; i < n; i++)
      y[i] = x[i-1];

    if(output_type == 1)
      printf("%d\n", 42);
    else {
      for(int i = 0; i < n; i++)
	printf("%ld ", y[i]);
      printf("\n");
    }
    return 0;
}

