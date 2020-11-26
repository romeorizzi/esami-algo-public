/*
Generatore di input per il problema poldo_sums.

USI SPECIALI:
arg1 < 0: i casi di esempio

input: N M T HMIN HMAX SEED

    T: 0 -> normal
       1 -> 2 after 1
       2 -> one interval
       3 -> all paths 

*/
#include<iostream>
#include<cassert>
#include<cstdlib>
#include<random>
#include<unordered_set>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<pair<int, pair<int, int>>> ops_vec;

#define MAX_LEN 1000000

int N, M, T, HMIN, HMAX, GMIN, GMAX, seed;

void stampa_esempio(int i) {

    switch (i) {
        case 1: {

cout << R"(3 6
0 0 0
2 0 2
1 0 5
2 0 2
1 1 5
1 2 5
2 0 2
)";
            break;
        }

        case 2: {
cout << R"(5 4
3 -5 -5 -5 2
2 0 2
2 2 4
2 1 3
2 0 4
)";  
        break;
        }

        case 3: {
cout << R"(8 4
1 2 2 2 3 3 4 5
2 1 7
2 2 6
1 6 -1
2 0 7
)";  
            break;
        }
    }


}

int rand_between(int start, int end) {
    if (start >= end) {
        cerr << start << " >= " << end << endl;
        assert(start < end);
    }
    return rand() % (end - start) + start;
}

int rand_height(int hmin, int hmax) {
    // int h = rand_between(0, (int)pow(hmax - hmin + 1, 1.0/4.0) + 2);
    // return min(hmax, hmin + h * h + rand() % 10);
    return rand_between(hmin, hmax + 1);
}

void generate_ap(int sz, int start, int height, int &i, vector<int> &A, ops_vec &M) {
    // cerr << "Target height " << height << endl;
    int m_st = i;
    for (int j = start; j < sz; j++) {
        if (A[j] != height) {
            M[i++] = {1, {j, height - A[j]}};
            // assert(abs(height - A[j]) <= 20000);
            // cerr << "Delta " << height - A[j] << endl;
            A[j] = height;
        }
    }
}

int find_ap(int start, int end, int& sz, vector<int> &A) {
    
    int best_height = -0x7FFFFFFF;
    int best_idx = start;
    int best_rsize = 1;

    int size = 1;
    int height = A[start];
    int index = start;
    
    for (int i = start+1; i <= end; i++) {
        if (A[i] == height) {
            size++;
        }
        else {
            if (best_height < height) {
                best_height = height;
                best_idx = index;
                best_rsize = size;

                height = A[i];
                size = 1;
                index = i;
            }
        }
    }

    sz = best_rsize;
    return best_idx;
}

int main(int argc, char** argv) {
    assert(argc > 0);

    N = atoi(argv[1]);

    if (N < 0) {
        stampa_esempio(-N);
        return 0;
    }

    M = atoi(argv[2]);
    T = atoi(argv[3]);
    HMIN = atoi(argv[4]);
    HMAX = atoi(argv[5]);
    seed = atoi(argv[6]);

    srand(seed);

    vector<int> A(N * 2);

    for (int i = 0; i < N;) {
        int run_length = rand_between(1, min(7, N - i + 1));

        if (T == 2) run_length = 1;

        int height = rand_height(HMIN, HMAX);
        int end_val = i + run_length;

        for (; i < end_val; i++) {
            A[i] = height;
        }

    }

    cout << N << " " << M << endl;
    for (int i = 0; i < N; i++) {
        if (i) cout << " ";
        cout << A[i];
    }
    cout << endl;

    ops_vec OPS(M * 2);

    int gap = min(max(3, M / 2), 5);


    int start = rand_between(0, max(1, (N - 2)));
    int end = rand_between(0, max(1, (N - start)) + start);

    if (T == 3) {
        start = 0;
        end = N - 1;
    }

    int last_gap = 0;

    for (int i = 0; i < M;) {

        // cerr << "Op " << start << " - " << end << endl;
        // for (int j = 0; j < N; j++) {
        //     cerr << A[j] << " ";
        // }
        // cerr << endl;

        bool is_query;
        if (T == 1) { 
            is_query = i > M / 2;
        } else {
            is_query = i - last_gap > gap || i == M - 1;
        }

        if (is_query) {
            random_shuffle(OPS.begin() + last_gap, OPS.begin() + i);

            if (i == M - 1) {
                start = 0;
                end = N - 1;
            }

            OPS[i] = {2, {start, end}};

            start = rand_between(0, max(1, (N - 2)));
            end = min(N, rand_between(0, max(1, (N - start))) + start);

            if (T == 3) {
                start = 0;
                end = N - 1;
            }

            last_gap = i;
            i++;
        }
        else {
            if((rand() % 7 == 0 || T == 2)) {
                int sz = 1;
                int start_ap = find_ap(start, end, sz, A);

                int gap = min(M - i - 1, rand_between(1, sz + 1) + 4);
                for (int j = start_ap; j < start_ap + gap && j < N; j++) {
                    int delta = rand_height(HMIN, HMAX) - A[j];
                    // assert(abs(delta) <= 20000);

                    OPS[i++] = {1, {j, delta}};
                    A[j] += delta;
                }
            }
            else {
                int gap_size = min(N - start, min(M - i - 1, rand() % 3 + 7));
                int gap_start = rand_between(start, max(start + 1, end - gap_size));
                assert(max(start + 1, end - gap_size) <= N);
                assert(gap_start + gap_size <= N);
                generate_ap(gap_size, gap_start, rand_height(HMIN, HMAX), i, A, OPS);
            }

        }
    }

    for (int i = 0; i < M; i++) {
        cout << OPS[i].first << " " << OPS[i].second.first << " " << OPS[i].second.second << endl;
    }

    return 0;
}
