#include <assert.h>
#include <stdio.h>

const int MAXN = 1000000;
const int MAXM = 1000000;

int N, M;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        // TODO: memorizzare arco
    }

    int esito[N];

    // TODO: calcolare esito

    for(int u = 0; u < N; u++) {
        printf("%d ", esito[u]);
    }
    printf("\n");
}
