#include <cassert>
#include <cstdio>
#include <algorithm>

#define MAXN 1000000

int N;
int v[MAXN], dyn[MAXN+3];

int main() {
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
       scanf("%d", &v[i]);
    for(int i = N-1; i >= 0; i--) {
        dyn[i] = v[i] + std::max(dyn[i+2], dyn[i+3]);
    }

    printf("%d\n", dyn[0]);

    return 0;
}

