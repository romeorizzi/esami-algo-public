#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**9)

t, n, m = map(int,input().strip().split())
#print(f"t={t}, n={n}, m={m}")
    
bridges = [False] * m
num_components =  [0] + [1] * (n-1)

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
    global time, opent, low, bridges, num_components
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
            if low[z] >= opent[v]:
                num_components[v] += 1
        elif z != dad: # Update low value of v
            low[v] = min(low[v], opent[z])
    assert low[v]<=opent[v]
    if v == 0:
        assert num_components[v] == num_children_v
  
dfs(0, 0, 0)

if t==1:
    for e_index in range(m):
        print(1, end=" ") if bridges[e_index] else print(0, end=" ")
if t==2:
    for v in range(n):
        print(1, end=" ") if num_components[v] > 1 else print(0, end=" ")
if t==3:
    for v in range(n):
        print(num_components[v], end=" ")
print()
