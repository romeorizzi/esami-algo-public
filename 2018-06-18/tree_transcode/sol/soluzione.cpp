/**
 *  Soluzione di code_tree
 *
 *  Autore: Romeo Rizzi, 2018-06-15
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


int children2descendants(int root) {
// lavora sull'albero codificato nel vettore num_children[] come dati in lettura.   
// Ritorna il numero di nodi n' del sotto-albero radicato al nodo <root>.
// Inoltre, scrive la codifica in formato num_descendants di tale sottoalbero nel sotto-array num_descendants[root, root +n'-1].
  int n_descendants = 1; // ogni nodo ha quantomeno se stesso come discendente
  for(int i = 1; i <= num_children[root]; i++)
    n_descendants += children2descendants(root +n_descendants);
  return num_descendants[root] = n_descendants;
}

void descendants2children(int root) {
// lavora sull'albero codificato nel vettore num_descendants[] come dati in lettura.   
// Scrive la codifica in formato num_children di tale sottoalbero nel sotto-array num_children[root, root +n'-1], dove n' è il numero di nodi del sotto-albero radicato al nodo <root>
  num_children[root] = 0;
  int n_opened = 1; // un discendente aperto, il nodo root stesso
  while(n_opened < num_descendants[root]) {
    num_children[root]++;
    descendants2children(root+n_opened);
    n_opened += num_descendants[root+n_opened];
  }
}


int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
  int input_format, output_format; // either 1 (num_children) or 2 (num_descendants);
  scanf("%d", &input_format);
  printf("%d ", output_format = 3 - input_format);
  if(input_format == 1) {
    int n = 0; // invariant: while reading the input, n will precisely stand for the number of those nodes v for which num_children[v] has already been read. 
    int declared = 1; // at least the root is out there.
    while( n < declared ) {
      scanf("%d", &num_children[n]);
      declared += num_children[n];
      n++;
    }  

    assert( children2descendants(0) == n);

    for(int i = 0; i < n; i++)
      printf("%d ", num_descendants[i]);
    printf("\n");
  }
  else {
    assert(input_format == 2);
    scanf("%d", &num_descendants[0]);
    int n = num_descendants[0]; //just a shorthand for the total number of nodes
    for(int i = 1; i<n; i++)
      scanf("%d", &num_descendants[i]);

    descendants2children(0);

    for(int i = 0; i < n; i++)
      printf("%d ", num_children[i]);
    printf("\n");
  }  

  return 0;
}
