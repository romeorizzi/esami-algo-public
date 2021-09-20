#!/usr/bin/env python3

"""FILE: generatore.py  problem: LIP  last change: 2021-09-16  author: Romeo Rizzi
 Randomly generates a simple undirected graph G=(V,E) on N=n^d nodes which is the Cartesian product of d identical graphs on n nodes of the given type.
 The types are:
  t=1: K_n, the complete graph on n nodes 
  t=2: P_n, the path on n nodes
  t=3: C_n, the cycle on n nodes
 The labels of the nodes are permuted in 0..N-1.
 The graph is weighted on the nodes: to each node is associated a positive natural in [1,2N].
 The first line of the stream prduced has the format "n m".
 The second line prints the weights on the nodes.
 Finally, the edge list is printed sorted, one edge per line, and where each edge uv is printed as "u v" so that u < v.
"""

usage="""Generatore per il problema "LIP".
 Usage syntax:
   > generatore t n d seed
PARAMETERS:
 * t: basic graph type in [1,3]: 1 clique, 2 path, 3 cycle
 * n: number of nodes of each basic type graph isomorphic copy
 * d: dimensionality of the Cartesian product. That is, number of isomorphic copies of the basic graph to be combined by Cartesian product, in order to obtain the final graph.
 * seed: seed for the pseudo-random generation (relabeling of the nodes and weights for the nodes)
 */
"""

import sys
import random
from limiti import *

MAXN = 50000
MAXM = 200000

def basic_graph(t,n):
  V = set(range(n))
  if t==1: # complete graph K_n
    E = [ (i, j) for i in range(n-1) for j in range(i+1,n) ]
  elif t==2: # path P_n
    E = [ (i, i+1) for i in range(n-1) ]
  elif t==3: # cycle C_n
    E = [ (i, i+1) for i in range(n-1) ] +[(0,n-1)]
  else:
    assert False
  return (V,E)
  
def cartesian_product(G1,G2):
  """returns the Cartesian product of the two graphs G1 and G2.
     A graph G=(V,E) is the 2-tuple (V,E), where V is a set and E is a list of edges. An edge is list of lenght 2 of elements over V. 
  """
  V1,E1 = G1
  V2,E2 = G2
  V = { (v1,v2) for v1 in V1 for v2 in V2 }
  E = [ [(u,v2),(v,v2)]  for u,v in E1 for v2 in V2 ] + [ [(v1,u),(v1,v)]  for u,v in E2 for v1 in V1 ]
  return (V,E)

def shuffle_and_relabel(G):
  V,E=G
  n = len(V)
  new_V = set(range(n))
  relabel=list(range(n))
  random.shuffle(relabel)
  new_name = {}   # a map delivering brand new names for the nodes
  for v, old_v_name in zip(V,range(n)):
    new_name[v] = relabel[old_v_name]
  new_E = []
  for u,v in E:
    if new_name[u]<new_name[v]:
      new_E.append([new_name[u],new_name[v]])
    else:
      new_E.append([new_name[v],new_name[u]])
  new_E.sort()
  return (new_V,new_E)


def run(t, n, d, all_diff_vals):
    V_basic,E_basic=basic_graph(t,n)
    V,E=basic_graph(t,n)
    for _ in range(d-1):
        #print(f"V={V}")
        #print(f"E={E}")
        V,E=cartesian_product( (V,E), (V_basic,E_basic) )
        #print(f"V={V}")
        #print(f"E={E}")
    V,E=shuffle_and_relabel( (V,E) )
    #print(f"V={V}")
    #print(f"E={E}")

    N = n**d
    assert len(V) == N
    assert len(E) <= MAXM
    print (N, len(E))
    if all_diff_vals:
        val=[2*i+1 for i in range(N) ]
        random.shuffle(val)
    else:
        val = [random.randint(1,2*N) for _ in range(N) ]
    for i in range(N):
        print(val[i],end=" ")
    print()
    for (u,v) in E:
        print(u, v)


if __name__ == "__main__":
    if len(sys.argv) != 6:
        print(usage)
        exit(1)

    t,n,d,all_diff_vals,seed = map(int, sys.argv[1:])
    N = n**d
    assert 1 <= t <= 3
    assert n >= 1
    assert d >= 1
    assert 0 <= all_diff_vals <= 1
    assert 1 <= N <= MAXN
    random.seed(seed)
    run(t,n,d,all_diff_vals)
