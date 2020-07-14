/*
USO 1:
arg1 -> t
arg2 -> N
arg3 -> Max K_i
arg4 -> seed
[arg5] -> vincitore (riferito al gioco singolo)
[arg6] -> che tavolo muove il computer (solo t = 1)
*/
#include<cstdlib>
#include<cassert>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>


#define NMAX 100000
#define KMAX 100000
using namespace std;
int main(int argc, char** argv) {    
    size_t t, N, MAX_K;
    bool winner = true;
    int seed;

    assert(argc >= 5);

    t = (size_t)atoi(argv[1]);
    assert(t == 1 || t == 2);

    N = (size_t)atoi(argv[2]);
    assert(N > 0 && N <= NMAX);
    vector<size_t> ret_list;
    ret_list.reserve(N + 1);

    MAX_K = atoi(argv[3]);
    assert(MAX_K >=0 && MAX_K < KMAX);
    if(MAX_K == 0) MAX_K = (KMAX) - 2;

    seed = atoi(argv[4]);
    srand(seed);

    if(argc > 5) {
        winner = (bool)atoi(argv[5]);
    }

    size_t current = 0u;
    for(size_t i = 0u; i < N - 1u; i++) {
        size_t temp =  1u + (unsigned long)(rand() % MAX_K);
        ret_list.push_back(temp);
        current ^= temp;
    }

    if(current) {
        if(winner) { //aggiungi qualcosa di diverso da XOR corrente
            size_t temp;
            do {
                temp = 1u + (rand() % MAX_K);
            }while(temp == current);
            ret_list.push_back(temp);
        } else { //aggiungi qualcosa di uguale allo XOR corrente
            ret_list.push_back(current);
        }
    } else {
        if(winner) { //aggiungi una roba random.
            ret_list.push_back(1u + (unsigned long)(rand() % MAX_K));
        } else { //aggiungi due volte una roba random. Modificando il numero degli N.
            size_t temp = 1u + (unsigned long)(rand() % MAX_K);
            ret_list.push_back(temp);
            ret_list.push_back(temp);
            N += 1u;
        }
    }

    cout << t << " " << N << endl;
    sort(ret_list.begin(), ret_list.end()); //cosi' li stampo a triangolo :)
    for(auto i : ret_list)
        cout << i << " ";
    cout << endl;

    //stampa mossa computer
    if(t == 2) {
        cout << 'T' << " " << ret_list[0] << " " << 0 << " " << 0;
    } else {
        char tavolo = rand() % 2 ? 'T' : 'N';
        if(argc > 6) {
            tavolo = argv[6][0];
            assert(tavolo == 'T' || tavolo == 'N');
        }
        auto x = ret_list[rand() % ret_list.size()];
        auto y1 = rand() % x;
        uint32_t y2 = 0;
        if(tavolo == 'T') {
            y2 = rand() % (x - y1);
        }
        cout << tavolo << " " << x << " "  << y1 << " " << y2;
    }
    cout << endl;

    return 0;
}
