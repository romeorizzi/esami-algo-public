/**
 *  Template per soluzione in c++ per il problema online_budget_opt
 *
 *  Romeo Rizzi, 2019-07-28
 *
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

    y[0] = B0;
    for(int i = 1; i < n; i++)
      y[i] = x[i-1];

    if(output_type == 1)
      cout << 42 << endl;
    else
      print_array(y, n);

    return 0;
}

