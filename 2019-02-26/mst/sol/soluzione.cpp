/*
  Giovanni Campagna <scampa.giovanni@gmail.com>

  Minimum Spanning Tree - implementazione con Prim
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

const int N_MAX = 10000;
const int M_MAX = 10000000;
const int W_MAX = numeric_limits<int>::max();

int N, M;
typedef vector<pair<int, int> > vicini_t;
typedef vector<vicini_t> lista_vicini_t;
lista_vicini_t lista_vicini;
vector<bool> visto;
int wsol;
stack<pair<int, int> > soluzione;

void prim() {
  priority_queue<pair<int, pair<int, int> > > coda;

  coda.push(make_pair(0, make_pair(0, -1)));
  while (!coda.empty()) {
    const pair<int, pair<int, int> >& e(coda.top());
    int peso = -e.first;
    int nodo = e.second.first;
    int from = e.second.second;

    coda.pop();
    if (visto[nodo])
      continue;

    visto[nodo] = true;
    wsol += peso;
    if (from != -1)
      soluzione.push(make_pair(from, nodo));

    const vicini_t& vicini(lista_vicini[nodo]);
    for (vicini_t::const_iterator i(vicini.begin()); i != vicini.end(); ++i) {
      int figlio = i->first;
      int peso = i->second;
      if (figlio != from && !visto[figlio])
	coda.push(make_pair(-peso, make_pair(figlio, nodo)));
    }
  }
}

int mst(int N, int M, int A[], int B[], int P[], int C[], int D[]) {
  ::N = N;
  ::M = M;

  assert (N >= 1 && N <= N_MAX);
  assert (M >= 2 && M <= M_MAX);

  lista_vicini.resize(N);
  visto.resize(N, false);
  for (int i(0); i < M; i++) {
    lista_vicini[A[i]].push_back(make_pair(B[i], P[i]));
    lista_vicini[B[i]].push_back(make_pair(A[i], P[i]));
  }

  prim();

  assert (wsol <= W_MAX);
  
  int x = 0;
  while(!soluzione.empty()) {
    const pair<int, int>& arco(soluzione.top());
    C[x] = arco.first;
    D[x] = arco.second;
    x++;
    soluzione.pop();
  }

  return wsol;
}

