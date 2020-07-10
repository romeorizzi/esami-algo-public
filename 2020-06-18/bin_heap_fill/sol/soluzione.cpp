#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

bool check_tree(vector<int> const& tree, vector<int> const& E, int node) {

    int crt = tree[node];

    int left_idx = node * 2 + 1;
    int right_idx = node * 2 + 2;

    if (left_idx < tree.size()) {
        if (E[left_idx] && tree[left_idx] < crt)
            return false;
        if (!check_tree(tree, E, left_idx)) return false;
    }

    if (right_idx < tree.size()) {
        if (E[right_idx] && tree[right_idx] < crt)
            return false;
        if (!check_tree(tree, E, right_idx)) return false;
    }
    
    return true;
}

bool find_solution(vector<int> &tree, 
                    vector<int> const& E, 
                    vector<int> const& F, 
                    set<int> &vals, 
                    int node,
                    bool root) {

    // Esco se trovo un nodo non-E o F che non è la radice del sottoalbero che sto considerando
    if ((F[node] || !E[node]) && !root) return true;

    int &val = tree[node];

    int left_idx = node * 2 + 1; // 2 * node + 1
    int right_idx = node * 2 + 2; // 2 * (node + 1)
    
    // Ricorsione nel sottoalbero
    if (left_idx < tree.size()) {
        if (!find_solution(tree, E, F, vals, left_idx, false)) return false;
    }

    if (right_idx < tree.size()) {
        if (!find_solution(tree, E, F, vals, right_idx, false)) return false;
    }

    if (!F[node]) {

        int upper_bound = 0x7FFFFFFF;

        if (left_idx < tree.size() && E[left_idx]) {
            upper_bound = min(upper_bound, tree[left_idx]);
        }

        if (right_idx < tree.size() && E[right_idx]) {
            upper_bound = min(upper_bound, tree[right_idx]);
        }

        if (tree[node] != -1) {
            exit(1);
        }

        assert(vals.size() > 0);

        tree[node] = *--vals.upper_bound(upper_bound);

        vals.erase(tree[node]);
    }

    if (right_idx < tree.size()) {
        if(tree[node] > tree[right_idx] && E[right_idx]) {
            return false;
        }
    }
    if (left_idx < tree.size()) {
        if(tree[node] > tree[left_idx] && E[left_idx]) {
            return false;
        }
    }

    return true;
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

    if (t == 1) {
        cout << check_tree(A, E, 0) << endl;
    }

    if (t == 2) {
        set<int> values;

        vector<pair<int, int>> fpos;

        bool origcheck = check_tree(A, E, 0);


        for (int i = 0; i < N; i++) {
            if (!F[i]) {
                values.insert(A[i]);
                A[i] = -1;
            }
            else {
                fpos.emplace_back(A[i], i);
            }
        }

        sort(fpos.rbegin(), fpos.rend());

        bool sol = true;

        for (int i = 0; i < fpos.size() && sol; i++) {
            sol &= find_solution(A, E, F, values, fpos[i].second, true);
        }

        if (!F[0] && sol) {
             sol &= find_solution(A, E, F, values, 0, true);
        }

//        for (int i = 0; i < N; i++) {
//            assert(A[i] >= 0);
//        }

        bool check = check_tree(A, E, 0);

        assert(check == sol);

        cout << sol << endl;
    }

    // if (t == 2)
}
