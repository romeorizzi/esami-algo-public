#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int M;
vector<int> A;

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
            }
            break;
            case 2: {
                cin >> x >> y;
                int totint = 0;
                for (int j = x; j <= y; j++) {
                    if (A[j]) totint++;
                }
                cout << totint << endl;
            }
            break;
        }
    }

    return 0;
}
