/*
Generatore di input per il problema bin_hea_seq.

arg1: tipo del task
    1 -> solo verifica
    2 -> correzione
    3 -> enumerazione

USI SPECIALI:
arg1 < 0: i casi di esempio


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

int T, N, E, F, errcnt, seed;

vector<int> generate_sequence(int size) {
    vector<int> tmp(size);
    iota(tmp.begin(), tmp.end(), 1);
    random_shuffle(tmp.begin(), tmp.end());
    return tmp;
}

void print_output(vector<int> input, vector<bool> e_mask, vector<bool> f_mask) {
    cout << N << " " << T << endl;
    for (int i = 0; i < input.size() ; i++) {
        if (i) cout << " ";
        cout << input[i];
    }
    cout << endl;

    e_mask[0] = 0;
    for (int i = 0; i < e_mask.size() ; i++) {
        if (i) cout << " ";
        cout << e_mask[i];
    }
    cout << endl;

    for (int i = 0; i < f_mask.size() ; i++) {
        if (i) cout << " ";
        cout << f_mask[i];
    }
    cout << endl;
}

void build_heap(vector<int> &input, vector<bool> const& epos, int index) {

    int &val = input[index];

    int left_idx = index * 2 + 1; // 2 * index + 1
    int right_idx = index * 2 + 2; // 2 * (index + 1)

    int smallest = index;

    // Top down phase
    if (left_idx < input.size() && epos[left_idx] && input[left_idx] < input[smallest]) {
        smallest = left_idx;
    }

    if (right_idx < input.size() && epos[right_idx] && input[right_idx] < input[smallest]) {
        smallest = right_idx;
    }

    if (smallest != index) {
        swap(val, input[smallest]);
        build_heap(input, epos, smallest);
    }
}

void stampa_esempi(int i) {
    switch (i) {
        case 1: cout << "7 1\n2 3 1 5 4 7 6\n0 1 1 1 1 1 1\n0 0 0 0 0 0 0" << endl; break;
        case 2: cout << "7 1\n2 3 1 5 4 7 6\n0 1 0 1 1 1 1\n0 0 0 0 0 0 0" << endl; break;
        case 3: cout << "7 2\n2 3 1 5 4 7 6\n0 1 1 1 1 1 1\n0 0 0 0 0 0 0" << endl; break;
        case 4: cout << "7 2\n2 3 1 5 4 7 6\n0 1 1 1 1 1 1\n1 0 0 0 0 0 0" << endl; break;
    }
}

void make_anticatena(vector<bool> &F) {


    for (int i = 1; i < F.size(); i++) {

        int parent = (i - 1) / 2;

        if (F[parent] && F[i]) {
            if (rand() % 3 == 0) {
                F[parent] = 0;
            }
            else {
                F[i] = 0;
            }
        }  
    }

}

int main(int argc, char** argv) {
    assert(argc > 0);

    T = atoi(argv[1]);

    if (T < 0) {
        stampa_esempi(-T);
        return 0;
    }

    N = atoi(argv[2]);
    E = atoi(argv[3]);
    F = atoi(argv[4]);
    errcnt = atoi(argv[5]);
    seed = atoi(argv[6]);

    srand(seed);

    auto heap = generate_sequence(N);

    vector<bool> emask(N, 0);
    for (int i = 1; i < E; i++) emask[i] = 1;
    random_shuffle(emask.begin() + 1, emask.end());

    vector<bool> fmask(N, false);
    for (int i = 0; i < F; i++) fmask[i] = true;
    random_shuffle(fmask.begin(), fmask.end());


    // Quinto subtask!
    if (seed / 1000 == 5) {
        make_anticatena(fmask);
    }


    // Costruisco l'heap corretto
    for (int i = N/2-1; i >= 0; i--) {
        build_heap(heap, emask, i);
    }

    vector<int> nonfpos;
    vector<int> fpos;
    for (int i = 0; i < N; i++) {
        if (!fmask[i]) nonfpos.push_back(i);
        else fpos.push_back(i);
    }

    int toterrors = errcnt;
    if (T == 2) toterrors = nonfpos.size();

    for (int i = 0; i < toterrors; i++) {
        int pa = rand() % nonfpos.size();
        int pb = rand() % nonfpos.size();
        swap(heap[nonfpos[pa]], heap[nonfpos[pb]]);
    }

    if (T == 2) {
        if (!((errcnt == 0) || !fpos.empty())) {
            cerr << T << " " << N << " " << seed << endl;
            exit(1);
        }
        for (int i = 0; i < errcnt; i++) {
            int pa = rand() % fpos.size();
            int pb = rand() % N;
            swap(heap[fpos[pa]], heap[pb]);
        }
    }

    print_output(heap, emask, fmask);

    return 0;
}
