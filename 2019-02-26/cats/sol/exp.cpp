// As dp.cpp, but does not memoize partial solutions.

#include <iostream>
#include <cmath>

#define MAXN 1000

using namespace std;

int M[MAXN], F[MAXN];
int nM, nF;

int score(int posM, int posF) {
    return abs(M[posM] - F[posF]);
}

int max_alignment(int posM, int posF) {
    // Check that we have some remaining positions
    if (posM == nM || posF == nF) 
        return 0;
    // Try to align or to skip one of the two
    int align = score(posM, posF) + max_alignment(posM + 1, posF + 1);
    int skipM = max_alignment(posM + 1, posF);
    int skipF = max_alignment(posM, posF + 1);
    return max(align, max(skipM, skipF));
}

int main() {
    cin >> nM >> nF;
    for (int i = 0; i < nM; i++)
        cin >> M[i];
    for (int i = 0; i < nF; i++)
        cin >> F[i];

    cout << max_alignment(0, 0) << endl;
}
