/*
    Backtracking dei possibili match.
*/

#include<cstdlib>
#include<iostream>
#include<fstream>
#include<vector>
#include<set>
using namespace std;


istream &in(cin);
ostream &out(cout);

// Lista di adiacenza dai nodi a sx ai nodi a dx
vector<set<int> > adjlist;
vector<int> match;
vector<int> inv_match;
int N, M;

int main() {
    in >> N >> M;
    adjlist.resize(N);
    match.resize(N);
    inv_match.resize(N);

    for(int i=0;i<M;i++) {
        int src, dst;
        in >> src >> dst;
        adjlist[src].insert(dst);
        if(i<N) {
            match[src] = dst;
            inv_match[dst] = src;
        }
    }

    for(int i=0;i<N;i++) {
        for(set<int>::iterator icand = adjlist[i].begin();
            icand != adjlist[i].end(); icand++) {
            }
        for(int j=i+1;j<N;j++) {
            if(adjlist[i].find(match[j]) != adjlist[i].end() &&
               adjlist[j].find(match[i]) != adjlist[j].end()) {
                int tmp = match[i];
                match[i] = match[j];
                match[j] = tmp;
                for(int k=0;k<N;k++) {
                    out << k << " " << match[k] << endl;
                }
                return 0;
            }
        }
    }

    out << -1 << endl;
    return 0;
}
