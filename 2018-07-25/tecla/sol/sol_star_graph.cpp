/* solutore del problema Tecla su grafi dove nodo 0 sia universale
   Romeo 2018-07-15
*/

#include <iostream>

using namespace std;

int N, M;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N >> M;

    int a, b;
    for (int i=0; i<M; i++) {
        cin >> a >> b;
        if(a*b != 0)
	  i = M;
    }

    cout << 3 << endl;
    cout << 0 << " " << a << " " << b << " " << 0 << endl;

    return 0;
}
