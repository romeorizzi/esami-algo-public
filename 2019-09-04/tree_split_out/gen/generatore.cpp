/* FILE: generatore.cpp riadattato da randSpecchio.cpp (made: 16-Sep-2013)
 * last change: 2019-09-04 author: Romeo Rizzi
 * This program generates a random rooted ordered tree on n nodes encoded as in the "specchio" problem or in its num_descendants variation as in problem "tree_transcode".
 * The tree is first generated as a string of 2 chars: '(' and ')' and later encoded and possibly transcoded as in problem "tree_transcode".
 * Usage syntax:
 *   > generatore.cpp n format max_children seed
 * if max_children=1 every node has precisely one child except the only leaf.
 * if max_children=2 every node has at most 2 children.
 * if max_children != 1,2 no bound on the number of children.
 * 
 * if format=1 the tree is encoded as in the "specchio" problem, with every node reporting the number of its children. 
 * if format=2 the tree is encoded as in the "specchio" problem but every node reports the number of its desendants rather than the number of its children. 
 * if format=3 the tree is encoded as in the "tree_transcode" problem: evey node reports its depth (distance from the root) both when it is opened and when it is closed in the DFS visit of the tree. 
 * 
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

const int MAX_N = 1000000;
char s[2*MAX_N];
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


int RandNumber(int min, int max) {
  /* returns an integer in [min, max]
   * see Stroustrup "The c++ Programming Language" 3th edition pg. 685
   * for comments on the following manipulation choice.
   * In particular, considerations on the bad quality of low bits come into account.
   */
  return min + (int) ( (max-min +1) * (double( rand()-0.000000000001 ) / RAND_MAX ) );
}

void randomParenth(int a, int b, int max_children) {
  if (a >= b) return;
  assert( (a-b) % 2 );
  s[a] = '(';  s[b] = ')';
  if(max_children == 1) // costruiamo un path
    randomParenth(a+1, b-1, max_children);
  else {
    int dist_mate_of_a_from_b = 2*RandNumber(0, (b-a)/2);
    if( dist_mate_of_a_from_b == 0 ) randomParenth(a+1, b-1, max_children);
    else {
      int c = b - dist_mate_of_a_from_b;
      s[c] = ')';
      s[c+1] = '(';
      randomParenth(a+1, c-1, max_children);
      if(max_children == 2) // ogni nodo massimo due figli
	randomParenth(c+2,b-1, max_children);
      else
        randomParenth(c+1,b, max_children);
    }
  }
}


int encodeRootedTree(int root_left, int posW) {
  // encodes into num_childrens the tree represented by the well-balanced parenthesis formula in s starting from the '(' in position root_left. It also returns the position root_right of the closing ')' matching the '(' in position root_left.
  // cout << "root_left = " << root_left << ",  posW = " << posW << endl;
  int n_children = 0; int root_right = 1 + root_left;
  while( s[root_right] == '(' ) {
    n_children++;
    root_right = 1 + encodeRootedTree(root_right, posW + (root_right-root_left +1)/2);
  }
  num_children[posW] = n_children;
  return root_right;
}

int depth[MAX_N*2]; /*stores the tree encoded by listing the depth of each node as encontered while traversing the tree in preorder. The depth id reported both when opening and closing the subtree. */

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


int main(int argc, char** argv) {
  srand(time(NULL));
  int n = atoi(argv[1]);
  assert( n >= 1);
  int format = atoi(argv[2]);
  assert( format == 1 || format == 2 || format == 3 );
  int max_children  = atoi(argv[3]);
  if(argc > 4) srand( atoi(argv[4]) );

  randomParenth(0, 2*n-3, max_children);
  // for(int i = 0; i < 2*n-2; i++) cout << i%10; cout << endl;
  // for(int i = 0; i < 2*n-2; i++)
  //   cout << s[i];
  // cout << endl;

  int root_right = -1;
  int n_children = 0;
  while( root_right < 2*n-3) {
    n_children++;
    root_right = encodeRootedTree(root_right +1, 1+(root_right+1)/2);
  }
  num_children[0] = n_children;

  assert( children2descendants(0) == n);

  posW = 0;
  read_descendants_format(0,0);

  cout << format << " ";
  if(format == 1) 
      for(int i = 0; i < n; i++)
        cout << num_children[i] << " ";
  if(format == 2) 
      for(int i = 0; i < n; i++)
        cout << num_descendants[i] << " ";
  if(format == 3) 
      for(int i = 0; i < 2*n; i++)
        printf("%d ", depth[i]);
  printf("\n");


  return 0;
}
