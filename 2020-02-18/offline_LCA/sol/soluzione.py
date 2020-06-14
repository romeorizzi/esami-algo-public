#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
sys.setrecursionlimit(100000)
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione di offline-LCA, esame algoritmi 2020-02-18
   Autore: Romeo Rizzi
"""

DEBUG = False

MAXN = 1000000
MAXQ = 1000000
N, Q = map(int,input().split())
assert 1 <= N <= MAXN
assert 0 <= Q <= MAXN
p = list(map(int,input().split()))
assert len(p) == N
roots = [v for v in range(N) if p[v] == -1]
print(len(roots))

# aggiungiamo un nodo (nodo N) che faccia da radice universale:
for r in roots:
    p[r] = N
children = [ [] for _ in range(N+1) ]
for v in range(N):
    #print(v,p[v])
    children[p[v]].append(v)

if DEBUG:
    print(f"p={p}, children={children}")

query_on_uv = [ [] for _ in range(N+1) ]
answer_to_query = [0]*Q # assume the answer to each query is false
for i in range(Q):
    u, v, w = map(int,input().split())
    assert u != -1 and v != -1
    if w == -1:
        w = N
    if u == v == w:
        answer_to_query[i] = 1
    query_on_uv[u].append((i,v,w))
    query_on_uv[v].append((i,u,w))

# notice that the answers to all queries with u = v are now correctly set

openT = [None]*(N+1)
closeT = [None]*(N+1)
last_touchT = [None]*(N+1)
t=0
def dfs(v):
    global t
    if DEBUG:
        print(f"called dfs(v={v},t={t})")

    openT[v] = t
    last_touchT[v] = t
    t += 1
    for u in children[v]:
        dfs(u)
        last_touchT[v] = t
    for i,u,w in query_on_uv[v]:
        if openT[w] != None and openT[u] != None and openT[w] <= openT[u] < openT[v] and closeT[w] == None:
        # we get here iff w is a strict ancestor of v and an ancestor of u
            if w == u:
               answer_to_query[i] = 1
            if closeT[u] != None and last_touchT[w] >= closeT[u]:
               answer_to_query[i] = 1
    closeT[v] = t
    t += 1
    
dfs(N)
for i in range(Q):
    print(answer_to_query[i])
    
if DEBUG:
    print(f"node v={list(range(N+1))}")
    print(f"openT={openT}")
    print(f"closeT={closeT}")

    
