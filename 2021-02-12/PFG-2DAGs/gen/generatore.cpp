/* FILE: generatore.cpp  problem: PFG-2DAGs  last change: 10-Feb-2021  author: Romeo Rizzi
 * Randomly generates two DAGs of type t, with n1/n2 nodes and m1/m2 arcs. Plus a list of p pairs in V1xV2.
 * t=1: labels of the nodes randomly permuted, anyhow integers in [0,n).
 * t=2: (u,v) in A => u<v
 * t=3: (i-1,i) in A for every i in (0,n)
 * Usage syntax:
 *   > randDAG t n1 m1 n2 m2 p seed
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_N = 100000; int n1,n2; // num nodes.
const int MAX_M = 100000; int m1,m2; // num arcs.
int t,p; // type of the DAG (as explained above) and number of pairs.
const int TAIL=0, HEAD=1;
int arc[MAX_M][2]; // l'arco j-esimo e' (arcs[j][TAIL], arcs[j][HEAD])
int perm_n[MAX_N], perm_m[MAX_M];
// perm_n ci viene utile per permutare i nodi solo alla fine, appena prima dell'output. E con perm_m permutiamo gli archi.

inline void swap(int &a, int &b) { int tmp = a; a = b; b = tmp; }

void generaPerm_random_uniform(int *perm, int n) {
   for(int i=n-1; i > 1; i--)
     swap( perm[i], perm[ (rand() % i) + 1 ] );
   // for(int i=0; i < n; i++)
   //   cout << perm[i] << " ";
   // cout << endl;  
}

int RandNumber(int min, int max) {
  /* returns an integer in [min, max)
   * see Stroustrup "The c++ Programming Language" 3th edition pg. 685
   * for comments on the following manipulation choice.
   * In particular, considerations on the bad quality of low bits come into account.
   */
 return min + (int) ( (max-min) * (double(rand()) / RAND_MAX) );
}

void gen_a_DAG(int n, int m, int t) {
  // genera un unpermuted DAG compatibile al total order 0,1,2,3, ..., n-1
  // di type t=1=2 o t=3 
  for(int j = 0; j < m; j++) {
     int a, b; // the two endpoints of arc j
     if(t==3) {
        if(j < n-1) { a = j; b = j+1; }
	else { a = RandNumber(0,n-2); b = RandNumber(a+2,n); }
     } else {a = RandNumber(0,n-1); b = RandNumber(a+1,n); }
     arc[j][TAIL] = a; arc[j][HEAD] = b;
  } // END: DAG generato
  //for(int j = 0; j < m; j++) // debug printing 
  //   cout << arc[j][TAIL] << " " << arc[j][HEAD] << endl;  
}

int main(int argc, char** argv) {
  t = atoi(argv[1]); n1 = atoi(argv[2]); m1 = atoi(argv[3]); n2 = atoi(argv[4]); m2 = atoi(argv[5]); p = atoi(argv[6]); 
  srand(time(NULL));  if(argc > 7) srand( atoi(argv[7]) );
  
  gen_a_DAG(n1, m1, t);
  for(int i = 0; i < n1; i++)  perm_n[i] = i;
  for(int i = 0; i < m1; i++)  perm_m[i] = i;
  if(t==1) {
    //cout << "perm_n= ";
    generaPerm_random_uniform(perm_n, n1);
  }
  //cout << "perm_m= ";
  generaPerm_random_uniform(perm_m, m1);
  cout << n1 << " " << m1 << endl;
  for(int j = 0; j < m1; j++)
      cout << perm_n[ arc[perm_m[j]][TAIL] ] << " " << perm_n[ arc[perm_m[j]][HEAD] ] << endl;

  gen_a_DAG(n2, m2, t);
  for(int i = 0; i < n2; i++)  perm_n[i] = i;
  for(int i = 0; i < m2; i++)  perm_m[i] = i;
  if(t==1) {
    //cout << "perm_n= ";
    generaPerm_random_uniform(perm_n, n2);
  }
  //cout << "perm_m= ";
  generaPerm_random_uniform(perm_m, m2);
  cout << n2 << " " << m2 << endl;
  for(int j = 0; j < m2; j++)
      cout << perm_n[ arc[perm_m[j]][TAIL] ] << " " << perm_n[ arc[perm_m[j]][HEAD] ] << endl;

  cout << p << endl;
  for(int j = 0; j < p; j++) 
    cout << RandNumber(0,n1) << " " << RandNumber(0,n2) << endl;
  
  return 0;
}
