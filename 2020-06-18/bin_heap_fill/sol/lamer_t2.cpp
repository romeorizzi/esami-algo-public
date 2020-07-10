#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

int ecnt = 0;

void check_tree(vector<int> const& tree, vector<int> const& E, int node) {

    int crt = tree[node];

    int left_idx = node * 2 + 1;
    int right_idx = node * 2 + 2;

    if (left_idx < tree.size()) {
        if (E[left_idx] && tree[left_idx] < crt)
            ecnt++;
        check_tree(tree, E, left_idx);
    }

    if (right_idx < tree.size()) {
        if (E[right_idx] && tree[right_idx] < crt)
            ecnt++;
        check_tree(tree, E, right_idx);
    }
}

int main() {

    int t, N; 
    
    cin >> N >> t;

    vector<int> A(N);
    vector<int> E(N);
    vector<int> F(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> E[i];
    }
    E[0] = 0;

    for (int i = 0; i < N; i++) {
        cin >> F[i];
    }

    if (t == 2) {
        set<int> values;

        vector<pair<int, int>> fpos;

        check_tree(A, E, 0);
        if (ecnt > N/5) cout << 0 << endl;
        else cout << 1 << endl;
    }
}
