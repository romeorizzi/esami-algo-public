#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int N;
int M[100000];
int Z[100000];
vector<int> G, P;

int S[100000];
int OS[100000];
int I[100000];

int X[100000];
int F[100000];

void upd(int x, int pos, int val) {
    x++;

    while (x <= N) {
        if (F[x - 1] < val) {
            F[x - 1] = val;
            X[x - 1] = pos;
        }
        x += x & -x;
    }
}

pair<int, int> get(int x) {
    x++;
    pair<int, int> sol = {0, -1};
    while (x) {
        if (sol.first < F[x - 1]) {
            sol.first = F[x - 1];
            sol.second = X[x - 1];
        }
        x -= x & -x;
    }
    return sol;
}

int compute(int n) {

    if (M[n]) return M[n];

//    int diff = 0;
//    for (int i = n - 1; i >= 0; i--) {
//        diff += G[i];
//
//        if (S[i] - S[n] <= 0) {
//            int current = compute(i);
//            if (current > best) {
//                best = current;
//                prev = i;
//            }
//        }
//    }

    int limit = (int)distance(OS, upper_bound(OS, OS+N, S[n])) - 1;

    auto val = get(limit);
    int best = val.first;
    int prev = val.second;

//    assert(best == val.first);
//    assert(M[prev] == M[val.second]);

    Z[n] = prev;
    M[n] = best + 1;

    upd(I[n], n, M[n]);

    return M[n];
}

int main(int argc, char const *argv[])
{
    cin >> N;

    fill(X, X + N, -1);

    G.resize(N);
    P.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> P[i] >> G[i];
    }
    
    int best = 0;
    int idx = 0;

    S[N - 1] = G[N - 1];
    for (int i = N - 1; i >= 0; i--) {
        S[i] = S[i + 1] + G[i];
    }
    for (int i = 0; i < N; i++) S[i] += P[i];

    vector<pair<int, int>> sorted(N);
    for (int i = 0; i < N; i++) {
        sorted[i] = {S[i], i};
    }
    sort(sorted.begin(), sorted.end());

    for (int i = 0; i < N; i++) {
        OS[i] = sorted[i].first;
        I[sorted[i].second] = i;
    }

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
        cout << val;
    }


    cout << endl;

    return 0;
}
