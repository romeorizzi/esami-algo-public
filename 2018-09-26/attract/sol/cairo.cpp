#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>

const unsigned MAXN = 1000000;

int N, M;
int x[MAXN];

std::vector<int> adj_i[MAXN], adj_o[MAXN];
int counter[MAXN];

int d[MAXN];

const int debug = 0;

int main()
{
#ifdef EVAL
    assert(freopen("input.txt", "r", stdin));
    assert(freopen("output.txt", "w", stdout));
#endif

    scanf("%d%d", &N, &M);
    for (int u = 0; u < N; u++)
    {
        scanf("%d", &x[u]);
    }

    for (int i = 0; i < M; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        adj_o[u].push_back(v);
        adj_i[v].push_back(u);
    }

    std::queue<int> Q;
    Q.push(0);

    d[0] = 0;
    counter[0] = 1;

    for (int u = 1; u < N; u++)
    {
        d[u] = -1;
    }

    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();

        if(debug) fprintf(stderr, "v:%2d, d[v]:%2d\n", v, d[v]);
        for (int u : adj_i[v])
        {
            counter[u]++;
            if(debug) fprintf(stderr, "%2d [%2d] -> %2d\n", u, counter[u], v);
            if (!x[u] && counter[u] == 1 || x[u] && counter[u] == adj_o[u].size())
            {
                assert(d[u] == -1);
                d[u] = d[v] + 1;
                Q.push(u);
            }
        }
    }

    for (int u = 0; u < N; u++)
    {
        printf("%d ", d[u]);
    }

    printf("\n");

    return 0;
}
