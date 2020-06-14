/* solutore WRONG per attract, problema per esame Algorimi 2018-09-26
   Romeo 2018-09-18
*/

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

const unsigned MAXN = 1000000;
int N, M;
int x[MAXN];
vector<int> enters[MAXN];

int d[MAXN], out_deg[MAXN];

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
	out_deg[a]++;
        enters[b].push_back( a );
    }

    for (int i=0; i<N; i++)
        d[i] = -1;
    
    for (int i=0; i<N; i++)
        cout << d[i] << " ";
    cout << endl;

    return 0;
}
