/*
 * Alice Cortinovis
 * 
 * MST con algoritmo di Kruskal
 */

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <fstream>
#include <stdio.h>

#define MAXN 10001
#define MAXM 1000000

using namespace std;

struct archi{
    int a, b;
    long long w;
};

vector< pair<int, long long int> > G[MAXN];
archi ARCHI[MAXM];
long long sol;
vector<pair<int, int> > archi_sol;
int N, M;
int p[MAXN];

bool comp(archi x, archi y) {
    if (x.w != y.w) return (x.w < y.w);
    if (x.a != y.a) return (x.a < y.a);
    return (x.b < y.b);
}

int FIND(int x) {
    if (x == p[x]) return x;
    else return p[x] = FIND(p[x]);
}

void UNION(int x, int y) {
    int px = FIND(x);
    int py = FIND(y);
    if (px == py) return;
    p[px] = py;
}

int mst(int N, int M, int A[], int B[], int P[], int C[], int D[]) {
    ::N = N;
    ::M = M;
    for (int i=0; i<M; i++) {
        ARCHI[i].a = A[i];
        ARCHI[i].b = B[i];
        ARCHI[i].w = P[i];
        G[ARCHI[i].a].push_back(make_pair(ARCHI[i].b, ARCHI[i].w));
        G[ARCHI[i].b].push_back(make_pair(ARCHI[i].a, ARCHI[i].w));
    }
    sort(ARCHI, ARCHI+M, comp);
    for (int i=0; i<N; i++) p[i] = i;
    for (int i=0; i<M; i++) {
        if (FIND(ARCHI[i].a) != FIND(ARCHI[i].b)) {
            UNION(ARCHI[i].a, ARCHI[i].b);
            sol = sol + ARCHI[i].w;
            archi_sol.push_back(make_pair(ARCHI[i].a, ARCHI[i].b));
        }
    }
    
    for (int i=0; i<(int)archi_sol.size(); i++) {
        C[i] = archi_sol[i].first;
        D[i] = archi_sol[i].second;
    }
        
    return sol;
}
