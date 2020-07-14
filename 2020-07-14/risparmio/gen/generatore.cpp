/*
Generatore di input per il problema poldo_sums.

Input: N, M, tipo, seed

USI SPECIALI:
arg1 < 0: i casi di esempio
tipo = 0: normale
tipo = 1: tutte le operazioni di tipo 1 sono prima di quelle di tipo 2
tipo = 2: durante una query, nell'intervallo richiesto non ci sono 2 lampadine consecutive
tipo = 3: l'intervallo delle query è sempre [0,N-1]

*/
#include<iostream>
#include<cassert>
#include<cstdlib>
#include<random>
#include<unordered_set>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX_LEN 1000000

int N, M, tipo, seed;

void stampa_esempio(int i) {

    switch (i) {
        case 1: {
            cout << "3 7" << endl;
            cout << "1 0" << endl;
            cout << "1 2" << endl;
            cout << "1 1" << endl;
            cout << "2 0 2" << endl;
            cout << "1 1" << endl;
            cout << "2 0 2" << endl;
            cout << "2 1 2" << endl;
        }
        break;
    
        case 2: {
            cout << "10 10" << endl;
            cout << "2 0 9" << endl;
            cout << "1 5" << endl;
            cout << "1 6" << endl;
            cout << "1 2" << endl;
            cout << "2 1 7" << endl;
            cout << "1 1" << endl;
            cout << "1 1" << endl;
            cout << "1 3" << endl;
            cout << "1 6" << endl;
            cout << "2 0 8" << endl;
        }
        break;    
    }


}

int A[100000];

void make_row(int start, int end, int &min_, int& max_, vector<int> &ops) {
    min_ = min(min_, start);
    max_ = max(max_, end);

    for (int i = start; i <= end; i++) {
        ops.push_back(i);
        A[i] = !A[i];
    }
}

typedef pair<int, pair<int, int>> op_t;

int main(int argc, char** argv) {
    assert(argc > 0);

    N = atoi(argv[1]);

    if (N < 0) {
        stampa_esempio(-N);
        return 0;
    }

    M = atoi(argv[2]);
    tipo = atoi(argv[3]);
    seed = atoi(argv[4]);

    srand(seed);

    int minq = 0x7FFFFFFF;
    int maxq = 0;

    vector<int> tops;
    vector<op_t> final_ops;

    for (int i = 1; i <= M; i++) {

        if (i % 20 == 0 || i == M) {

            // random_shuffle(tops.begin(), tops.end());

            for (auto x : tops) {
                final_ops.push_back({1, {x, 0}});
                // cout << "1 " << x << endl;
            }

            tops.clear();

            if (tipo == 3) {
                final_ops.push_back({2, {0, N-1}});
                // cout << "2 0 " << (N - 1) << endl;
            }
            else {

                minq = min(minq, maxq);

                int query_min = max(0, rand() % (minq + 1));
                int query_max = min(N-1, rand() % (N - maxq + 1) + maxq);


                final_ops.push_back({2, {query_min, query_max}});

                // cout << "2 " << query_min << " " << query_max << endl;
            }

            minq = 0x7FFFFFFF;
            maxq = 0;
        }
        else {
            int remaining = 20 - i % 20;

            int start = rand() % N;

            if (tipo == 3) {
                for (;;) {
                    if (A[start] || (
                        (!start || !A[start-1]) &&
                        (start == N - 1 || !A[start+1])
                    )) {
                        make_row(start, start, minq, maxq, tops);
                        break;
                    }
                    start = rand() % N;            
                }
            }
            else {

                int length = min(rand() % remaining, N - start - 1) + 1;

                make_row(start, start + length - 1, minq, maxq, tops);

                i += length - 1;
            }
        }
    }

    if (tipo == 1) {
        stable_sort(final_ops.begin(), final_ops.end(), [](op_t const& a, op_t const& b) {
            return a.first < b.first;
        });
    }

    cout << N << " " << final_ops.size() << endl;

    for (auto op : final_ops) {
        cout << op.first << " " << op.second.first;
        if (op.first == 2) cout << " " << op.second.second;
        cout << endl;
    }

    return 0;
}
