// Assume that the two sequences are non-drecreasing.

#include <iostream>
#include <algorithm>
#include <cmath>

#define MAXN 1000

using namespace std;

int M[MAXN], F[MAXN];
int nM, nF;

int main() {
    cin >> nM >> nF;
    if (nM >= nF) {
        for (int i = 0; i < nM; i++)
            cin >> M[i];
        for (int i = 0; i < nF; i++)
            cin >> F[i];
    } else {
        for (int i = 0; i < nM; i++)
            cin >> F[i];
        for (int i = 0; i < nF; i++)
            cin >> M[i];
        swap(nM, nF);
    }

    // Now F is always shorter than M.
    // We try to place it at the beginning of M or at the end.

    int best = 0;

    // Begin of M.
    for (int skip = 0; skip < nF; skip++) {
        int score = 0; 
        for (int i = 0; i < nF - skip; i++)
            score += abs(M[i] - F[i + skip]);
        best = max(best, score);
    }

    // End of M.
    for (int skip = 0; skip < nF; skip++) {
        int score = 0;
        for (int i = 0; i < nF - skip; i++)
            score += abs(M[nM - 1 - i] - F[nF - 1 - i - skip]);
        best = max(best, score);
    }

    cout << best << endl; 

}
