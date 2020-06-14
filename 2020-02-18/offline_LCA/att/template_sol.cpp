/**
 *  Template per soluzione in c++ per il problema offline-LCA
 *
 *  Romeo Rizzi, per l'appello di algoritmi 2020-02-18
 *
 */

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

//const int DEBUG = 0;
const int DEBUG = 1;

const int MAXN = 100000;
const int MAXQ = 100000;
int N,Q;
int p[MAXN];
int answer_to_query[MAXQ];
std::vector<int> children[MAXN];

int main() {
  scanf("%d%d", &N, &Q);
  assert(N>=1); assert(N<=MAXN);
  assert(Q>=0); assert(Q<=MAXQ);
  for(int i = 0; i < N; i++)
    scanf("%d", &p[i]);


  for(int v = 0; v<N; v++) {
    //print(v,p[v]);
    children[p[v]].push_back(v);
  }

  if(DEBUG)
      for(int v = 0; v<N; v++) {
        printf("nodo v=%d, p[%d] = %d\n%lu figli: ",v,v,p[v],children[v].size());
	for (int u : children[v])
          printf("%d ",u);
	printf("\n");
      }


  for(int i = 0; i < Q; i++)
    printf("%d ", answer_to_query[i]);
  
  return 0;
}

