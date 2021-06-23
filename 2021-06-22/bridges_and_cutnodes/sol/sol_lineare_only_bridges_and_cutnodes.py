#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**9)

t, n, m = map(int,input().strip().split())
#print(f"t={t}, n={n}, m={m}")
    
bridges = [False] * m
cutnodes =  [False] * n

edges = {}
nei = [ [] for v in range(n) ]
for i in range(m):
    u,v = map(int,input().strip().split())
    #print(f"u={u}, v={v}")
    nei[u].append(v)        
    nei[v].append(u)
    edges[(u,v)] = i
    edges[(v,u)] = i

#print(f"nei={nei}")
#print(f"edges={edges}")
    
time = 1
opent = [None] * n
low = [None] * n

def dfs(h, v, dad): # the recursion height h is present only to facilitate debugging
    global time, opent, low, bridges, cutnodes
    assert h <= n
    #print(f"called dfs(h={h}, v={v}, dad={dad})")
    low[v] = opent[v] = time
    time += 1
    num_children_v = 0
    for z in nei[v]:
        if opent[z] == None:
            num_children_v += 1
            dfs(h+1, z, v)
            low[v] = min(low[v], low[z])
            if low[z] > opent[v]:
                bridges[edges[(v,z)]] = True
            if low[z] >= opent[v] and v != 0:
                cutnodes[v] = True
        elif z != dad: # Update low value of v
            low[v] = min(low[v], opent[z])
    assert low[v]<=opent[v]
    if v == 0:
        if num_children_v > 1:
            cutnodes[v] = True
  
dfs(0, 0, 0)

if t==1:
    for e_index in range(m):
        print(1) if bridges[e_index] else print(0)
if t==2:
    for v in range(n):
        print(1) if cutnodes[v] else print(0)
