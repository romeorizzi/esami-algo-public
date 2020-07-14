#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int M;
vector<int> A;

int F[100000];

void upd(int x, int val) {
    // printf("Upd : %d by %d\n", x, val);
    x++;

    while (x <= N) {
        F[x - 1] += val;
        x += x & -x;
    }
}

int get(int x) {
    x++;
    int sol = 0;
    while (x) {
        sol += F[x - 1];
        x -= x & -x;
    }
    return sol;
}


int main(int argc, char const *argv[])
{
    cin >> N >> M;

    A.resize(N, 0);

    for (int i = 0; i < M; i++) {
        int t, x, y; cin >> t;

        switch (t) {
            case 1: {
                cin >> x;
                A[x] ^= 1;
                // If it's on
                if (A[x]) {

                    // and the previous is off, a new range starts here
                    if (!x || !A[x - 1]) {
                        upd(x, 1);
                    }

                    // If the next one is on, it's no longer the start of a light range
                    if (x < N - 1 && A[x + 1]) {
                        upd(x + 1, -1);
                    }
                }
                // If it's off, we have multiple cases:
                else if (!A[x]) {

                    // If the previous is off, this light was the start of a range, and now it's not.
                    if (!x || !A[x - 1]) {
                        upd(x, -1);
                    }

                    // If the next light is on, it's the start of a new range
                    if (x < N - 1 && A[x + 1]) {
                        upd(x + 1, 1);
                    }
                }
            }
            break;
            case 2: {
                cin >> x >> y;
                int intlast = get(y);
                int intfirst = x ? get(x - 1) : 0;

                // printf("FIRST: [%d]%d LAST: [%d]%d\n", x, intfirst, y+1, intlast);
                bool offbyone = A[x] && (x && A[x - 1]);
                int totint = intlast - intfirst + offbyone;
                cout << totint << endl;
            }
            break;
        }
    }

    return 0;
}
