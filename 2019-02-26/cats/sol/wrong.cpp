// WRONG
// Sum everything as already aligned.

#include <iostream>
#include <cmath>

#define MAXN 1000

using namespace std;

int M[MAXN], F[MAXN];
int nM, nF;

int main() {
    cin >> nM >> nF;
    for (int i = 0; i < nM; i++)
        cin >> M[i];
    for (int i = 0; i < nF; i++)
        cin >> F[i];

    int res = 0;
    for (int i = 0; i < min(nM, nF); i++)
        res += abs(M[i] - F[i]); 

    cout << res << endl;
}
