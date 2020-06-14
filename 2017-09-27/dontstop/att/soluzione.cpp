#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1000000;
const int MAXM = 1000000;

int N, M;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d%d", &N, &M);

    vector<int> adj[N]; // adj[u] = nodi che hanno un arco verso u
    int deg[N]; // deg[u] = numbero di archi uscenti da u, o -1 se rimosso

    for(int u = 0; u < N; u++) {
        deg[u] = 0;
    }

    for(int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        assert(0 <= a && a <= N);
        assert(0 <= b && b <= N);
        assert(a != b);

        deg[a]++;
        adj[b].push_back(a);
    }

    int esito[N];

    // TODO: calcolare esito

    for(int u = 0; u < N; u++) {
        printf("%d ", esito[u]);
    }
    printf("\n");
    return 0;
}
