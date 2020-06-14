/**
 *  online_budget_opt
 *
 *  Autore: Romeo Rizzi, 2019-07-28
 *
 *  Costo di questa soluzione: lineare.
 *
 *  Descrizione: greedy dal fondo.
 */

#include <cassert>
#include <iostream>
using namespace std;

const int MAX_N = 1000000;
const int MAX_VAL = 10;

int n, B0, output_type, x[MAX_N], q[MAX_N], is_index_of_last_opportunity[MAX_N];
long int y[MAX_N];

template <class T>
void print_array(T *v, int len) {
  for(int i = 0; i < len; i++)
    cout <<  v[i] << " ";
  cout << endl;
}

int main() {
    cin >> n >> B0 >> output_type;
    for(int i = 0; i < n; i++)
       cin >> x[i];
    for(int i = 0; i < n; i++)
       cin >> q[i];
    //print_array(x, n);
    //print_array(q, n);

    int max_so_far_q = -1;
    for(int i = n-1; i >= 0; i--)
      if(q[i] > max_so_far_q) {
	max_so_far_q = q[i];
	is_index_of_last_opportunity[i] = 1; // i is the index of a max so far of q from the right
      }

    int B = B0, num_gemme = 0;
    for(int i = 0; i < n; i++) {
      if(is_index_of_last_opportunity[i]) {
	y[i] = B;
	num_gemme += y[i]*q[i];
	B = 0;
      }
      B += x[i];
    }

    if(output_type == 1)
      cout << num_gemme << endl;
    else
      print_array(y, n);

    return 0;
}

