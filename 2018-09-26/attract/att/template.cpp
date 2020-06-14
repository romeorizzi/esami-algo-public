/* template per attract, problema per esame Algorimi 2018-09-26
   Romeo 2018-09-18
*/

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

const unsigned MAXN = 1000000;
int N, M;
int x[MAXN];
vector<int> exits[MAXN], enters[MAXN];

int d[MAXN];

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif

    cin >> N >> M;

    for (int i=0; i<N; i++) {
        cin >> x[i];
    }

    for (int i=0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        exits[a].push_back( b );
        enters[b].push_back( a );
    }


    // ToDO: risolvere il problema!

    
    for (int i=0; i<N; i++)
        cout << d[i] << " ";
    cout << endl;

    return 0;
}
