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
    }

    int count[N+1];
    count[0] = N; // we can make an unlimited amount of useless shots
    for(int i = 1; i <= N; i++) {
        count[i] = 0;
    }

    for(int left = 0, cur = 0, right = 0; cur < N; cur++) {
        right = max(right, min(cur + H[cur] - 1, N-1));
        assert(left <= cur && cur <= right);
        if(cur == right) {
            int size = right-left + 1;
            count[size]++;
            left = cur+1;
        }
    }

    for(int s = 1; s <= N; s++) {
        if(false) fprintf(stderr, "count[%d] = %d\n", s, count[s]);
    }

    int size = N;
    int tot = 0;
    for(int used = 0; used < N; used++) {
        assert(count[size] >= 0);
        while(count[size] == 0) {
            size--;
        }
        tot += size;
        count[size]--;
        printf("%d ", tot);
    }
    printf("\n");

    return 0;
}
