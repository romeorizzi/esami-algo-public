#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int N;
int M;
int P;
vector<char> A;
vector<char> B;
vector<int> C;

bool VIS[1024][1024];
int MEM[1024][1024];

#define INF 1000000000

int calcola(int i, int j) {

    int best = INF;

    if (i == A.size()) {
        if (j == B.size()) return 0;
        else return best;
    }

    if (j == B.size()) return best;

    if (VIS[i][j]) return MEM[i][j];

    if (A[i] == B[j]) {
        best = min(best, calcola(i + 1, j + 1));
    }

    for (int k = i + 1; k < A.size() && k - i < C.size(); k++) {
        best = min(best, calcola(k, j) + C[k - i]);
    }

    VIS[i][j] = true;

    return MEM[i][j] = best;
}

int main(int argc, char const *argv[])
{
    cin >> N >> M >> P;

    A.resize(N+1, 0);
    B.resize(M+1, 0);

    cin >> A.data();
    cin >> B.data();

    assert(A.back() == 0);
    assert(B.back() == 0);
    
    C.resize(P + 1);

    for (int i = 0; i < C.size(); i++) {
        cin >> C[i];
    }

    int result = calcola(0, 0);

    if (result >= INF) cout << -1 << endl;
    else cout << result << endl;

    return 0;
}
