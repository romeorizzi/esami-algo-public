#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**9)

t, n, m = map(int,input().strip().split())
#print(f"t={t}, n={n}, m={m}")
    
edge = []
for i in range(m):
    u,v = map(int,input().strip().split())
    edge.append([u,v])    

def num_connected_components():
    nei = [ [] for v in range(n) ]
    for u,v in res_edge:
        #print(f"u={u}, v={v}")
        nei[u].append(v)        
        nei[v].append(u)
    
    reached = [False] * n

    def dfs(v):
        nonlocal reached
        #print(f"called dfs(v={v})")
        reached[v] = True
        for z in nei[v]:
            if not reached[z]:
                dfs(z)

    num_components = 0
    for v in range(n):
        if not reached[v]:
            num_components += 1
            dfs(v)
    return num_components


if t==1:
    for e_index in range(m):
        res_edge = [e for e,i in zip(edge,range(len(edge))) if i != e_index]
        print(1) if num_connected_components() > 1 else print(0)
else:
    for v in range(n):
        res_edge = [{a,b} for a,b in edge if a != v and b != v]
        if v > 0:
            res_edge.append({0,v})
        else:
            res_edge.append({1,v})
            
        if t==2:
            print(1) if num_connected_components() > 1 else print(0)
        else:
            assert t==3
            print(num_connected_components())
