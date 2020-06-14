// DP
// dp[i][j] contains the best score that can be obtained aligning
// sequences males[i:] and females[j:].

#include <iostream>
#include <cmath>

#define MAXN 1000

using namespace std;

int M[MAXN], F[MAXN];
int nM, nF;
int dp[MAXN][MAXN];

int score(int posM, int posF) {
    return abs(M[posM] - F[posF]);
}

int max_alignment(int posM, int posF) {
    // Check that we have some remaining positions
    if (posM == nM || posF == nF)
        return 0;
    if (dp[posM][posF] == -1) {
        // Try to align or to skip one of the two
        int align = score(posM, posF) + max_alignment(posM + 1, posF + 1);
        int skipM = max_alignment(posM + 1, posF);
        int skipF = max_alignment(posM, posF + 1);
        dp[posM][posF] = max(align, max(skipM, skipF));
    }
    return dp[posM][posF];
}

int main() {
    cin >> nM >> nF;
    for (int i = 0; i < nM; i++)
        cin >> M[i];
    for (int i = 0; i < nF; i++)
        cin >> F[i];

    for (int i = 0; i < nM; i++)
        for (int j = 0; j < nF; j++)
            dp[i][j] = -1;

    cout << max_alignment(0, 0) << endl;
}
