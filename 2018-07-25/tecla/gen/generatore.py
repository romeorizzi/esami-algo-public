#!/usr/bin/env python2

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
from math import sqrt, ceil

usage="""Generatore di "oddcycle".

Parametri:
* T (tasktype)
* N (nodi)
* M (archi o altri nodi)
* S (seed)

Constraint:
* 1 <= N <= %d
* 2 <= T <= 6
""" % (MAXN)



def run(N, M, T):
    assert N >= 3

    # clique
    if T == 2:
        g = {}
        for v in xrange(N):
            for u in xrange(v):
                g[(u,v)] = 1
        M = len(g)

    # star su nodo 0 universale piu' altri archi a caso
    if T == 3:
        g = {}
        for v in xrange(1,N):
            g[(0,v)] = 1
        g[(N/2, N/4)] = 1  # un solo arco aggiuntivo
        assert N >= 4  # assicura che l'arco aggiuntivo vada bene
        M = len(g)

    # 2-regular graph (2 odd cycles on even end odd nodes)
    if T == 4:
        assert (N % 2 == 0) and ( (N/2) %2 == 1)
        g = {}
        for i in xrange(N):
            g[(i,(i+2) % N)] = 1
        M = len(g)

    # (2 bipartite even cycles on even end odd nodes, add bipartite edges and a non bipartite one on the even nodes)
    if T == 6:
        assert (N % 4 == 0)
        assert M <= (N/2)*((N+1)/2) + 1
        g = {}
        myM = 0
        for i in xrange(N):
            g[(i,(i+2) % N)] = 1
            myM += 1
        g[(2*(N/4),2*(N/4 +3))] = 1  # arco che distrugge bipartizione del grafo sui nodi di indice pari
        myM += 1
        assert N > 4  # assicura che l'arco aggiuntivo vada bene
        while myM < M:
            flip_coin = randint(0,1)
            u = 4*randint(0,N/4 -1) +2*flip_coin
            v = 4*randint(0,N/4 -1) +2*flip_coin
            if u != v:
                if (u,v) not in g:
                    if (v,u) not in g:
                        g[(u,v)] = 1
                        myM += 1

                        
    print N,M
    G = []
    for (u,v) in g:
        G.append((u,v))
    
    shuffle(G)
    for (u,v) in G:
        if randint(0,1) == 0:
            print u, v
        else:
            print v, u


if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)

    T, N, M, S = map(int, argv[1:])
    
    assert (2 <= T <= 6)
    assert (T != 5)
    seed(S)
    run(N, M, T)
