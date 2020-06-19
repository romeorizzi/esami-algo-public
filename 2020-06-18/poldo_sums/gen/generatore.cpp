/*
Generatore di input per il problema poldo_sums.

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

int N, PMAX, GMIN, GMAX, seed;

void stampa_esempio(int i) {

    switch (i) {
        case 1: {
            cout << "5" << endl;
            cout << "3 1\n8 2\n2 3\n9 4\n4 5" << endl;
            break;
        }

        case 2: {
            cout << "7" << endl;
            cout << "9 3\n4 -8\n2 7\n8 0\n4 -5\n5 0\n2 12" << endl;
            break;
        }

        case 3: {
            cout << "10" << endl;
            cout << "2748 283\n4278 -2128\n7332 332\n0 -1\n2833 0\n10000 3218\n1343 2222\n23 8853\n2223 3847\n8479 -847" << endl;
            break;
        }
    }


}


int main(int argc, char** argv) {
    assert(argc > 0);

    N = atoi(argv[1]);

    if (N < 0) {
        stampa_esempio(-N);
        return 0;
    }


    PMAX = atoi(argv[2]);
    GMIN = atoi(argv[3]);
    GMAX = atoi(argv[4]);
    seed = atoi(argv[5]);

    srand(seed);

    vector<int> P(N);
    vector<int> G(N);

    for (int i = 0; i < N; i++) {
        P[i] = rand() % (PMAX + 1);
        G[i] = rand() % (GMAX - GMIN + 1) + GMIN;
    }

    cout << N << endl;
    for (int i = 0; i < N; i++) {
        cout << P[i] << " " << G[i] << endl;
    }

    return 0;
}
