/*
Generatore di input per il problema poldo_sums.

Input: N, M, P, tipo, seed

USI SPECIALI:
arg1 < 0: i casi di esempio
tipo = 0: normale, b sottostringa di a
tipo = 1: b probabile non sottostringa di a (allineamento impossibile)
tipo = 2: tutte a e una z alla fine

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

int N, M, P, tipo, seed;

void stampa_esempio(int i) {

    switch (i) {
        case 1: {
            cout << "9 4 7" << endl;
            cout << "ASDFDSDFF" << endl;
            cout << "ASDF" << endl;
            cout << "0 1 3 3 2 8 6 7" << endl;
        }

        case 2: {
            cout << "7 2 5" << endl;
            cout << "ABCDEFG" << endl;
            cout << "AA" << endl;
            cout << "0 1 1 1 1 1" << endl;
        }
    }
}

string get_randstring(int sz, char common_start, char common_end, char rare_end) {

    vector<char> str;
    str.reserve(sz);

    for (int i = 0; i < sz; i++) {
        if (rand() % 3 || (rare_end == common_end)) {
            char c = rand() % (common_end - common_start + 1) + common_start;
            str.push_back(c);
        }
        else {
            char c = rand() % (rare_end - common_end) + common_end + 1;
            str.push_back(c);
        }
    }

    str.push_back(0);
    return string(str.data());
}

string get_substring(string const &s, int sz, int errors) {

    vector<int> indices(s.size());
    vector<bool> taken(s.size(), false);
    iota(indices.begin(), indices.end(), 0);

    random_shuffle(indices.begin(), indices.end());

    for (int i = 0; i < sz; i++) {
        taken[indices[i]] = true;
    }

    vector<char> result; result.reserve(sz);
    for (int i = 0; i < s.size(); i++) {
        if (taken[i]) result.push_back(s[i]);
    }
    assert(result.size() == sz);


    for (int i = 0; i < errors; i++) {
        int ia = rand() % sz;
        int ib = rand() % sz;
        swap(result[ia], result[ib]);
    }

    result.push_back(0);

    return string(result.data());
}

int main(int argc, char** argv) {
    assert(argc > 0);

    N = atoi(argv[1]);

    if (N < 0) {
        stampa_esempio(-N);
        return 0;
    }

    M = atoi(argv[2]);
    P = atoi(argv[3]);

    tipo = atoi(argv[4]);
    seed = atoi(argv[5]);

    srand(seed);

    int errors = 0;
    if (tipo % 2 == 1) errors = M / 2;

    auto a = get_randstring(N, 'A', 'F', 'Z');
    auto b = get_substring(a, M, errors);

    cout << N << " " << M << " " << P << endl;


    if (tipo == 2) {
        fill(a.begin(), a.end(), 'A');
        a.back() = 'Z';
        fill(b.begin(), b.end(), 'Z');
        assert(b.size() == 1);
    }

    cout << a << endl;
    cout << b << endl;

    cout << 0;
    for (int i = 1; i <= P; i++) {
        cout << " " << (rand() % 10000);
    }
    cout << endl;

    return 0;
}
