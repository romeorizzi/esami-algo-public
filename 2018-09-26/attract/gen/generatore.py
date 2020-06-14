#!/usr/bin/env python2

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "attract".

Parametri:
* N (nodi)
* N0 (nodi controllati dal pastore)
* M (archi)
* S (seed)

Constraint:
* 1 <= N <= %d
* 1 <= N0 <= N
* N <= M <= %d (da ogni nodo deve uscire almeno un arco)
""" % (MAXN,MAXM)



def run(N, N0, M):
    V = list(xrange(0,N))
    V_non_ovile = V[1::]
    V0 = [0,] + sample(V_non_ovile, N0-1)
    shuffle(V_non_ovile)
    relabels = [0,] + V_non_ovile
    
    g = {}
    for i in xrange(N):
        g[i,(i+1) % N] = 1
    while len(g) < M:
        u,v = sample(V, 2)   
        g[u,v] = 1

                        
    print N,M
    charact_vect_V0 = [1,]*N
    for v in V0:
        charact_vect_V0[v] = 0
    for v in V:
        print charact_vect_V0[v],
    print

    G = []
    for (u,v) in g:
        G.append((u,v))
    
    shuffle(G)
    for (u,v) in G:
        print relabels[u], relabels[v]


if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)

    N, N0, M, S = map(int, argv[1:])
    
    assert (1 <= N <= MAXN)
    assert (1 <= N0 <= N)
    assert (N <= M <= MAXM)
    seed(S)
    run(N, N0, M)
