#include <cassert>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000000;

int N;

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif

    scanf("%d", &N);
    int H[N];
    for(int i = 0; i < N; i++) {
        scanf("%d", &H[i]);
        H[i] = min(H[i], N-i);
    }

    sort(H,H+N);

    int tot = 0;
    for(int i = N-1; i >= 0; i--) {
        tot += H[i];
        tot = min(tot, N);
        printf("%d ", tot);
    }
    printf("\n");

    return 0;
}
