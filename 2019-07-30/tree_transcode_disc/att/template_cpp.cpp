/**
 *  Template per soluzione in c++ per il problema tree_transcode_disc
 *
 *  Romeo Rizzi, per l'appello di algoritmi 2019-07-28
 *
 */

#include <cassert>
#include <iostream>

using namespace std;

const int MAX_N = 1000000;

int n = 0, input_type;
int in_tree[MAX_N], out_tree[MAX_N];

int main() {
    // leggere l'input_type:
    cin >> input_type;

    // leggere la sequenza che codifica l'albero in input (in formato input_type):
    int val;
    while (cin >> val)
      in_tree[n++] = val;

    // in questo template di soluzione mi limito a ricopiare l'input in output (non sarà mai la soluzione corretta tranne che per alberi di un solo nodo):
    cout << input_type << ' ';
    for(int i=0; i<n; i++)
      cout << in_tree[i] << ' ';
    cout << endl;
    
    return 0;
}

