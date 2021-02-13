/* FILE: randDAG.cpp  last change: 9-Feb-2021  author: Romeo Rizzi
 * Randomly generates a DAG with n nodes and m arcs, of type t.
 * t=1: labels of the nodes randomly permuted, anyhow integers in [0,n).
 * t=2: (u,v) in A => u<v
 * t=3: (i-1,i) in A for every i in (0,n)
 * Usage syntax:
 *   > randDAG n m t seed
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_N =  100000; int n; // numero nodi.
const int MAX_M = 1000000; int m; // numero archi.
int t; // type of the DAG as explained above.
const int TAIL=0, HEAD=1;
int arc[MAX_M][2]; // l'arco j-esimo e' (arcs[j][TAIL], arcs[j][HEAD])
int perm_n[MAX_N], perm_m[MAX_M];
// perm_n ci viene utile per permutare i nodi solo alla fine, appena prima dell'output. E con perm_m permutiamo gli archi.

inline void swap(int &a, int &b) { int tmp = a; a = b; b = tmp; }

void generaPerm_random_uniform(int *perm, int n) {
   for(int i=n; i > 1; i--)
     swap( perm[i], perm[ (rand() % i) + 1 ] );
}

int RandNumber(int min, int max) {
  /* returns an integer in [min, max)
   * see Stroustrup "The c++ Programming Language" 3th edition pg. 685
   * for comments on the following manipulation choice.
   * In particular, considerations on the bad quality of low bits come into account.
   */
 return min + (int) ( (max-min) * (double(rand()) / RAND_MAX) );
}

int main(int argc, char** argv) {
  n = atoi(argv[1]); m = atoi(argv[2]); t = atoi(argv[3]);
  srand(time(NULL));  if(argc > 4) srand( atoi(argv[4]) );

  // BEGIN: genera un DAG compatibile al total order 0,1,2,3, ..., n-1
  for(int j = 0; j < m; j++) {
     int a, b; // the two endpoints of arc j
     if(t==3) {
        if(j < n-1) { a = j; b = j+1; }
	else { a = RandNumber(0,n-2); b = RandNumber(a+2,n); }
     } else {a = RandNumber(0,n-1); b = RandNumber(a+1,n); }
     arc[j][TAIL] = a; arc[j][HEAD] = b;
  } // END: generato un DAG compatibile al total order 0,1,2,3, ..., n-1

  for(int j = 0; j < m; j++)
      cout << arc[j][TAIL] << " " << arc[j][HEAD] << endl;  
  
  for(int i = 0; i < n; i++)  perm_n[i] = i;
  if(t==1)
    generaPerm_random_uniform(perm_n, n);
  for(int i = 0; i < m; i++)  perm_m[i] = i;
  generaPerm_random_uniform(perm_m, m);

  cout << n << " " << m << endl;
  for(int j = 0; j < m; j++)
      cout << perm_n[ arc[perm_m[j]][TAIL] ] << " " << perm_n[ arc[perm_m[j]][HEAD] ] << endl;

  return 0;
}
