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

    A.resize(N, 0);

    vector<int> queue;

    for (int i = 0; i < M; i++) {
        int t, x, y; cin >> t;

        switch (t) {
            case 1: {
                cin >> x;
                A[x] ^= 1;
                queue.push_back(x);
            }
            break;
            case 2: {
                cin >> x >> y;
                for (int w : queue) {
                    if (A[w] && ((w && A[w - 1]) || ((w < N-1) && A[w + 1]))) {
                        assert(false);
                        return 1;
                    }
                }
                queue.clear();
            }
            break;
        }
    }

    return 0;
}
