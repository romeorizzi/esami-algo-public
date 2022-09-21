#include<cstdlib>
#include<iostream>
#include<fstream>
#include<vector>
#include<list>

using namespace std;

int N, M;

// Lista di adiacenza per i soli nodi a destra, con destinazione
// i nodi a sinistra.
vector<list<int> > adjlist;
// Il matching suggerito.
int* match;

// Vettore dei visitati per la DFS.
bool* visited;

bool* is_ancestor;
#define NO_CYCLE 0
#define CYCLE_FOUND 1
#define CYCLE_ENDED 2

// Stato della ricerca del ciclo
int status = NO_CYCLE;
int cycle_root = 0;

void dfs(int current) {
    visited[current] = true;
    is_ancestor[current]=true;
    int matched = match[current];
    for(list<int>::iterator it = adjlist[matched].begin();
        it != adjlist[matched].end(); it++) {
        int dest = *it;
        if(dest != current) {
            if(visited[dest] && is_ancestor[dest]) {
                //fprintf(stderr, "ciclo con %d -> %d ...%d\n", current, matched, dest);
                status = CYCLE_FOUND;
                cycle_root = dest;
                match[dest] = matched;
                return;
            }
            if(!visited[dest]) {
                dfs(dest);
                if(status == CYCLE_FOUND) {
                    match[dest] = matched;
                    if(cycle_root == current)
                        status = CYCLE_ENDED;
                    return;
                }
                if(status == CYCLE_ENDED)
                    return;
            }
        }
    }
    is_ancestor[current]=false;
}

int main() {
  /*
    #ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
  */
    scanf("%d", &N);
    scanf("%d", &M);
    adjlist.resize(N);
    match = new int[N];
    visited = new bool[N];
    is_ancestor = new bool[N];
    for(int i=0;i<N;i++) {
        visited[i] = is_ancestor[i] = false;
    }

    for(int i=0;i<M;i++) {
        int src, dst;
        scanf("%d", &src);
        scanf("%d", &dst);
        if(i<N)
            match[src] = dst;
        else
            adjlist[dst].push_back(src);
    }

    for(int i=0;i<N;i++) {
        if(!visited[i])
            dfs(i);
        if(status == CYCLE_ENDED)
            break;
    }

    if(status == NO_CYCLE)
      printf("-1\n");
    else {
        for(int i=0;i<N;i++) {
            printf("%d %d\n",i,match[i]);
        }
    }
    return 0;
}
