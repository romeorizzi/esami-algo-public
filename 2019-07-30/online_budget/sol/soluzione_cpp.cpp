/**
 *  online_budget
 *
 *  Autore: Romeo Rizzi, 2019-07-28
 *
 *  Descrizione: ricorsione con memoizzazione.
 */

#include <cassert>
#include <iostream>
using namespace std;

const int MAX_N = 500;
const int MAX_VAL = 10;

const long int BIG_PRIME = 1000000007;

int n, B0, x[MAX_N];

template <class T>
void print_array(T *v, int len) {
  for(int i = 0; i < len; i++)
    cout <<  v[i] << " ";
  cout << endl;
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
  }
  return risp[i][B];
}

int main() {
    cin >> n >> B0;
    for(int i = 0; i < n; i++)
       cin >> x[i];
    //print_array(x, n);

    for(int i = 0; i <= n; i++)
      for(int b = 0; b <= MAX_VAL*n + B0; b++)
        risp[i][b] = -1;
    
    cout << num_histories_from(0,B0) << endl;
    
    return 0;
}

