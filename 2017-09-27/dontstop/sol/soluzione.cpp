#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1000000;
const int MAXM = 1000000;

int N, M;

#define dprintf(...)

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

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
    for(int u = 0; u < N; u++) {
        esito[u] = 0;
    }

    vector<int> pozzi;
    for(int u = 0; u < N; u++) {
        assert(deg[u] >= 0);
        if(deg[u] == 0) {
            pozzi.push_back(u);
        }
    }

    while(!pozzi.empty()) {
        int u = pozzi.back();
        pozzi.pop_back();

        dprintf("pozzo: %d\n", u);

        assert(deg[u] == 0);
        assert(esito[u] == 0);

        deg[u] = -1;
        esito[u] = -1;

        for(auto v : adj[u]) {
            if(deg[v] == -1) continue;
            dprintf("rimuovo: %d\n", v);
            assert(esito[v] == 0);
            deg[v] = -1;
            esito[v] = +1;
            for(auto w : adj[v]) {
                if(deg[w] == -1) continue;
                assert(deg[w] >= 1);
                deg[w]--;
                dprintf("decremento deg[%d] -> %d\n", w, deg[w]);

                if(deg[w] == 0) {
                    dprintf("nuovo pozzo: %d\n", w);
                    pozzi.push_back(w);
                }
            }
        }
    }

    for(int u = 0; u < N; u++) {
        printf("%d ", esito[u]);
    }
    printf("\n");
}
