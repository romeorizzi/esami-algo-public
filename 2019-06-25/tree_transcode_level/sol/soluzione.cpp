/**
 *  Soluzione di tree_transcode_three
 *
 *  Autore: Romeo Rizzi, 2019-06-25
 *
 *  Costo di questa soluzione: lineare.
 *
 *  Descrizione: ricodifica ricorsiva.
 */

#include <cassert>
#include <cstdio>

const int MAX_N = 1000000;
int num_children[MAX_N]; /*stores the tree encoded by listing in preorder the number of children, that is:
   num_children[i] = number of children of node i.
 (Where the IDs of the nodes are the first n natural numbers assigned in DFS-preorder starting from the root as node 0). */
int num_descendants[MAX_N]; /*stores the tree encoded by listing in preorder the number of descendants, that is:
   num_descendants[i] = number of descendants of node i.
 (Where the IDs of the nodes are the first n natural numbers assigned in DFS-preorder starting from the root as node 0). */
int depth[MAX_N*2]; /*stores the tree encoded by listing the depth of each node as encontered while traversing the tree in preorder. The depth id reported both when opening and closing the subtree. */


int read_children_format(int root, int d) {
// lavora sull'albero codificato nel vettore num_children[] come dati in lettura.   
// Ritorna il numero di nodi n' del sotto-albero radicato al nodo <root>.
// Inoltre, scrive la codifica in formato num_descendants di tale sottoalbero nel sotto-array num_descendants[root, root +n'-1].
  depth[root] = d;
  num_descendants[root] = 1; // ogni nodo ha quantomeno se stesso come discendente
  for(int i = 1; i <= num_children[root]; i++) {
    num_descendants[root] += read_children_format(root +num_descendants[root], d+1);
  }
  return num_descendants[root];
}

int posW;
void read_descendants_format(int root, int d) {
// lavora sull'albero codificato nel vettore num_descendants[] come dati in lettura.   
// Scrive la depth d del nodo sia in apertura che in chiusura su depth[posW]. Scrive inoltre la codifica in formato num_children di tale sottoalbero nel sotto-array num_children[root, root +n'-1], dove n' è il numero di nodi del sotto-albero radicato al nodo <root>
  depth[posW++] = d;
  num_children[root] = 0;
  int n_opened = 1; // un discendente aperto, il nodo root stesso
  while(n_opened < num_descendants[root]) {
    num_children[root]++;
    read_descendants_format(root+n_opened, d+1);
    n_opened += num_descendants[root+n_opened];
  }
  depth[posW++] = d;
}

int posR;
int read_depth_format(int root, int d) {
// lavora sull'albero codificato nel vettore depth[] come dati in lettura.   
// Ritorna il numero di nodi n' del sotto-albero radicato al nodo <root>.
// Inoltre, scrive la codifica in formato num_descendants di tale sottoalbero nel sotto-array num_descendants[root, root +n'-1].
  assert(depth[posR] == d);
  num_children[root] = 0;
  num_descendants[root] = 1; // ogni nodo ha quantomeno se stesso come discendente
  while(depth[++posR] > d) {
    num_descendants[root] += read_depth_format(root +num_descendants[root], d+1);
  }
  return num_descendants[root];
}




int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
  int input_format, output_format; // either 1 (num_descendants) or 2 (depth);
  scanf("%d", &input_format);
  printf("%d ", output_format = 3 - input_format);
  if(input_format == 1) {
    scanf("%d", &num_descendants[0]);
    int n = num_descendants[0]; //just a shorthand for the total number of nodes
    for(int i = 1; i<n; i++)
      scanf("%d", &num_descendants[i]);

    posW = 0;
    read_descendants_format(0,0);

    for(int i = 0; i < 2*n; i++)
      printf("%d ", depth[i]);
    printf("\n");
  }
  else {
    int n = 0;
    scanf("%d", &depth[n++]);
    scanf("%d", &depth[n++]);
    while( depth[n-1] > 0 )
      scanf("%d", &depth[n++]);

    assert( n % 2 == 0 );

    posR = 0;
    assert( read_depth_format(0,0) == n/2);

    for(int i = 0; i < n/2; i++)
      printf("%d ", num_descendants[i]);
    printf("\n");
  }  

  return 0;
}
