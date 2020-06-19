#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int M[100000];
int Z[100000];
vector<int> G, P;

int compute(int n) {

    if (M[n]) return M[n];

    int diff = 0;
    int best = 0;
    int prev = -1;
    for (int i = n - 1; i >= 0; i--) {
        diff += G[i];
        if (P[i] + diff <= P[n]) {
            int current = compute(i);
            if (current > best) {
                best = current;
                prev = i;
            }
        }
    }

    Z[n] = prev;
    M[n] = best + 1;
    return best + 1;
}

int main(int argc, char const *argv[])
{
    cin >> N;

    G.resize(N);
    P.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> P[i] >> G[i];
    }
    
    int best = 0;
    int idx = 0;

    for (int i = 0; i < N; i++) {
        int crt = compute(i);
        if (crt > best) {
            best = crt;
            idx = i;
        }
    }

    vector<int> sol;
    sol.reserve(best);

    while (idx >= 0) {
        sol.push_back(idx);
        idx = Z[idx];
    }

    reverse(sol.begin(), sol.end());

    cout << best << endl;

    bool first = true;

    for (int val : sol) {
        if (!first) cout << " ";
        first = false;
        cout << (val ? val + 1 : val - 1);
    }

    cout << endl;

    return 0;
}
