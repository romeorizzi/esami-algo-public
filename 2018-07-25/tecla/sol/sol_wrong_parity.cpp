/* solutore del problema Tecla che ritorna sempre un walk di parity errata (even)
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
        if(a*b == 0)
	  i = M;
    }

    int v = a;
    if( v == 0 )
      v = b;

    cout << 2 << endl;
    cout << 0 << " " << v << " " << 0 << endl;

    return 0;
}
