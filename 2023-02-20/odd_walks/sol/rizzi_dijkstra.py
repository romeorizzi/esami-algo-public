#!/usr/bin/env python3
# -*- coding: latin-1 -*-

N,M,PL,PC = map(int,input().split())
if PL == 2:
    PL = [0,1]
else:
    PL = [PL]
if PC == 2:
    PC = [0,1]
else:
    PC = [PC]

from queue import PriorityQueue
q = PriorityQueue()
q.put((0,0,0)) # key/dist,node,PL
out_arcs = [ [] for _ in range(N)]
for _ in range(M):
    a,b,c = map(int,input().split())
    out_arcs[a].append((b,c))
dist = [ {(0,0):-1,(0,1):-1,(1,0):-1,(1,1):-1} for _ in range(N)]
dist[0] = {(0,0):0,(0,1):-1,(1,0):-1,(1,1):-1}

while not q.empty():
    dist_u,u,pl = q.get()
    for v,c in out_arcs[u]:
        kind = (1-pl,(dist_u+c) % 2)
        if dist[v][kind] == -1 or dist[v][kind] > dist_u+c:
            dist[v][kind] = dist_u+c
            q.put((dist[v][kind],v,1-pl))  # key/dist,node,PL

            
def min_filtered_dist(dict_of_dists):
    good_dists = [dist for label,dist in dict_of_dists.items() if label[0] in PL and label[1] in PC and dist != -1]
    if len(good_dists)==0:
        return -1
    return min(good_dists)

print(' '.join([str(min_filtered_dist(dist[v])) for v in range(N)]))

    
