#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int N;
int M;
vector<int> A;

int main(int argc, char const *argv[])
{
    cin >> N >> M;

    A.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int i = 0; i < M; i++) {
        int t, x, y; cin >> t >> x >> y;

        switch (t) {
            case 1: {
                assert(x < N);
                // A[x] += y;
                // cerr << "Add " << y << " to " << A[x] << endl;
            }
            break;
            case 2: {

                if (x >= N || y >= N) {
                    cerr << x << " " << y << " " << N << endl;
                    assert(x < N && y < N);
                }

                int besth = -1000000;
                for (int i = x; i <= y; i++) {

                    int equal = 1;

                    for (int j = 1; j < 3 && (i + j) <= y; j++) {
                        if (A[i] == A[i + j]) equal++;
                    }

                    if (equal >= 3) besth = max(A[i], besth);
                }
                if (besth == -1000000) cout << "NESSUN_ALTOPIANO" << endl;
                else cout << besth << endl;

                // cerr << "A: ";
                // for (int i = 0; i < N; i++) {
                //     cerr << " " << A[i];
                // }
                // cerr << endl;
            }
            break;
            default: assert(false);
            break;
        }
    }

    return 0;
}
