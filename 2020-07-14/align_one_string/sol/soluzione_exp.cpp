#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int M;
int P;
vector<char> A;
vector<char> B;
vector<int> C;

#define INF 1000000000

int calcola(int i, int j) {

    int best = INF;

    if (i == A.size()) {
        if (j == B.size()) return 0;
        else return best;
    }

    if (j == B.size()) return best;

    if (A[i] == B[j]) {
        best = min(best, calcola(i + 1, j + 1));
    }

    for (int k = i + 1; k < A.size() && k - i < C.size(); k++) {
        best = min(best, calcola(k, j) + C[k - i]);
    }

    return best;
}

int main(int argc, char const *argv[])
{
    cin >> N >> M >> P;

    A.resize(N+1, 0);
    B.resize(M+1, 0);

    cin >> A.data();
    cin >> B.data();
    
    C.resize(P + 1);

    for (int i = 0; i < C.size(); i++) {
        cin >> C[i];
    }

    int result = calcola(0, 0);

    if (result >= INF) cout << -1 << endl;
    else cout << result << endl;

    return 0;
}
