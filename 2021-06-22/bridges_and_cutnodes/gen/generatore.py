#!/usr/bin/env python3

"""FILE: generatore.py  problem: bridges_and_cutnodes  last change: 2021-06-21  author: Romeo Rizzi
 Randomly generates a simple undirected graph G=(V,E) with a certain number of cutnodes and a certain number of bridges. To do so, it first generates a directed ordered tree T that will serve as a DFS-tree for G. Currently, T is just the binary tree with root in 0 (like the one for the binary heap implementation of priority queues).
"""

usage="""Generatore di "bridges_and_cutnode".
 Usage syntax:
   > generatore t n m b seed
PARAMETERS:
 * t: subtask type, also the first number in the instance to be generated
 * n: number of nodes, also the second number in the instance to be generated
 * m: number of edges, also the third number in the instance to be generated (NOTE HOWEVER: this number is taken only as an indication. We try to meet it while also producing enogh blocks)
 * b: number of bridges 
 * seed: seed for the pseudo-random generation
 */
"""

import sys
import random
from limiti import *

MAXN = 100000

def block(n, m):
  """yields a random Hamiltonian block with n nodes and m edges"""
  assert n > 1
  if n==2:
      return [ 2, (0,1) ]  # that is, two nodes and one edge
  assert n <= m
  assert m <= n*(n-1)//2
  Cn = [ (i, i+1) for i in range(n-1)] +[(0,n-1)]
  while len(Cn) < m:
      pair = tuple(random.sample(range(n),k=2) )
      edge=(min(pair[0],pair[1]), max(pair[0],pair[1]))
      if edge not in Cn:
          Cn += [edge]
  relabel=list(range(n))
  random.shuffle(relabel)
  B = [ (relabel[edge[0]], relabel[edge[1]]) for edge in Cn]
  return [n] + B  # that is, n nodes and m edges

def make_list_of_blocks(n, m, b):
    blocks = []
    N = 1
    M = 0
    for i in range(b):
        blocks.append(block(2,1))
        N += 1
        M += 1
        #print(f"N={N}, M={M}")
    while N < n:
        next_n = min(n-N+1, 2*(m-M)//(n-N))
        if next_n == n-N+1:
            next_m = max(min(m-M, next_n*(next_n-1)//2), next_n)
        next_m = min(next_n * ((m-M)//(n-N)), next_n*(next_n-1)//2)
        blocks.append(block(next_n,next_m))
        N += next_n-1
        M += next_m
        #print(f"N={N}, M={M}")
    #print(f"Hai prodotto una lista di {len(blocks)} blocchi")
    return blocks

def run(t, n, m, b):
    blocks = make_list_of_blocks(n, m, b)
    g = []
    n = 1
    m = 0
    for b in blocks:
        pinch_node = random.randint(0,n-1)
        num_nodes_of_b = b[0]
        map = [pinch_node] + [(n-1)+i for i in range(1,num_nodes_of_b)]
        g += [ (map[edge[0]], map[edge[1]]) for edge in b[1:]]
        n += num_nodes_of_b -1
        m += len(b[1:])
        
    print (t, n, m)
    relabel=list(range(n))
    random.shuffle(relabel)
    G = [ (min(relabel[edge[0]], relabel[edge[1]]), max(relabel[edge[0]], relabel[edge[1]])) for edge in g]
    G.sort()
    for (u,v) in G:
        print(u, v)


if __name__ == "__main__":
    if len(sys.argv) != 6:
        print(usage)
        exit(1)

    t,n,m,b,seed = map(int, sys.argv[1:])

    assert t in {1,2,3}
    assert (1 <= n <= MAXN)
    assert (1 <= m <= MAXM)
    assert (0 <= b <= m)
    random.seed(seed)
    run(t,n,m,b)
