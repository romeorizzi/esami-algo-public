// Assume that every male has the same value.
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

#define MAXN 1000

using namespace std;

int M, F[MAXN], diff[MAXN];
int nM, nF;

int main() {
    cin >> nM >> nF;
    for (int i = 0; i < nM; i++)
        cin >> M;
    for (int i = 0; i < nF; i++) {
        cin >> F[i];
        diff[i] = abs(M - F[i]);
    }

    // Sum the K highest values in the array diff.
    int K = min(nM, nF);
    sort(diff, diff + nF, greater<int>());    
    cout << accumulate(diff, diff + K, 0) << endl;
}
