#!/usr/bin/env python2

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "chordal_cliques".

Parametri:
* goal (int >= 0, task type)
* N (int >= 1, num nodi)
* Mmax (int >= 0, num archi max)
* yes_no (0/1, il grafo e` cordale? l'ordinamento e` lexBFS? l'ordinamento e` elimination scheme?)
* S (seed)

Constraint:
* 1 <= N <= %d
* N-1 <= Mmax <= %d (grafo connesso)
""" % (MAXN,MAXM)



def run(goal, N, Mmax, yes_no):
    G = [] # G e` una lista di al piu` Mmax archi, ossia di coppie di nodi in V
    # costruiremo G un nodo alla volta: 1 2 3 ... i sara` (prima del relabeling dei nodi) un ordinamento simpliciale del sottografo indotto G[{1,2,3, ..., i}] per ogni i <= N
    i_violation = randint(4,N) # ma se yes_no=0 la condizione sara` falsa sul nodo i = i_violation
    if goal <= 2 or yes_no == 1:
        i_violation = N+2

    clique = {1: [1] } # per ogni nodo i inserito teniamo traccia della sua unica clique massimale in G[{1,2,3, ..., i}]
    for i in xrange(2,N+1):
      if i != i_violation:
          j = randint(min(i-1,2),i-1)  
          if goal >= 3:
              if i != i_violation -1:
                  clq = clique[j]
              else:
                  clq = {v for v in clique[j] if v != 1}
          else:
              while j < i-1 and clique[j][-1] < clique[i-1][0]:
                  j += 1
              clq = {v for v in clique[j] if v != 1 and v > clique[i-1][0]}
              if len(clq) == 0:
                  clq = {clique[i-1][0]}
          m_incr_max = min(len(clq),Mmax-len(G)-N+i)
          m_incr = randint(min(m_incr_max,(Mmax-len(G))/(N-i+1)),m_incr_max)
          neigh_of_i = sample(clq, m_incr)
          for u in neigh_of_i:
              G.append((u,i))
          clique[i] = [i] + neigh_of_i
          clique[i].sort()
      else:
          G.append((i,1))
          G.append((i,i-1))
          clique[i] = [i-1,i]
    if goal == 1 and yes_no == 0:
        i_violation = randint(N/2,3*N/4)
        add = 1
        while len(clique[i_violation]) >= add and clique[i_violation][add-1] == add:
            add += 1
        assert add < i_violation-1
        G.append((i_violation-1,add))
    if goal == 2 and yes_no == 0:
        i_violation = randint(N/2,3*N/4)
        pos = 0
        while len(clique[i_violation-1]) > pos +2 and clique[i_violation][pos] == clique[i_violation-1][pos]:
            pos += 1
        if clique[i_violation][pos] > clique[i_violation-1][pos]:
            G.append((i_violation,clique[i_violation-1][pos]))
        
    print goal, N, len(G)
    shuffle(G)
    relabels = list(xrange(1,N+1))
    if goal <= 2:
        pass
    elif goal <= 5: 
        relabels = list(reversed(xrange(1,N+1)))
    elif goal == 6:
        shuffle(relabels)
    for (u,v) in G:
        if randint(0, 1):
           print relabels[u-1], relabels[v-1]
        else:
           print relabels[v-1], relabels[u-1]
               


if __name__ == "__main__":
    if len(argv) != 6:
        print usage
        exit(1)

    goal, N, Mmax, yes_no, S = map(int, argv[1:])
    
    assert (1 <= N <= MAXN)
    assert (N <= Mmax <= MAXM)
    assert (0 <= yes_no <= 1)
    seed(S)
    run(goal, N, Mmax, yes_no)
