#include <bits/stdc++.h>

using namespace std;

int R[110000][2][2];
vector<pair<int, int>> G[110000];

int main()
{
    int N, M, PL, PC;

    cin >> N >> M >> PL >> PC;

    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        assert(u < N);
        assert(v < N);
        G[u].push_back({v, w});
    }

    priority_queue<pair<int, pair<int, int>>> Q;

    Q.push({0, {0, 0}});

    memset(R, -1, sizeof(R));

    while (!Q.empty())
    {
        auto p = Q.top();
        Q.pop();

        int l = p.second.first;
        int u = p.second.second;
        int d = -p.first;

        // cout << "Visit node " << u << " at level " << l << " with distance " << d << endl;

        if (R[u][l % 2][d % 2] != -1)
            continue;

        R[u][l % 2][d % 2] = d;

        for (auto e : G[u])
        {
            int v = e.first;
            int w = e.second;

            // cout << "\t Push node " << v << " at level " << (l + 1) << " with distance " << (d + w) << endl;

            Q.push({-d - w, {l + 1, v}});
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (i)
            cout << " ";

        int result = -2;

        switch (PL)
        {
        case 0:
        {
            switch (PC)
            {
            case 0:
                result = R[i][0][0];
                break;
            case 1:
                result = R[i][0][1];
                break;
            case 2:
                result = (int)min((unsigned int)R[i][0][0], (unsigned int)R[i][0][1]);
                break;
            }
            break;
        }
        case 1:
        {
            switch (PC)
            {
            case 0:
                result = R[i][1][0];
                break;
            case 1:
                result = R[i][1][1];
                break;
            case 2:
                result = (int)min((unsigned int)R[i][1][0], (unsigned int)R[i][1][1]);
                break;
            }
            break;
        }
        case 2:
        {
            switch (PC)
            {
            case 0:
                result = (int)min((unsigned int)R[i][0][0], (unsigned int)R[i][1][0]);
                break;
            case 1:
                result = (int)min((unsigned int)R[i][0][1], (unsigned int)R[i][1][1]);
                break;
            case 2:
                result = (int)min(
                    min((unsigned int)R[i][0][0], (unsigned int)R[i][1][0]),
                    min((unsigned int)R[i][0][1], (unsigned int)R[i][1][1]));
                break;
            }
            break;
        }
        }

        assert(result != -2);
        cout << result;
    }
    cout << endl;
    return 0;
}
