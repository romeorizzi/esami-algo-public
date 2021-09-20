#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**9)

n, m = map(int,input().strip().split())
#print(f"n={n}, m={m}")
val = list(map(int,input().strip().split()))
nei = [ [] for v in range(n) ]
for i in range(m):
    u,v = map(int,input().strip().split())
    #print(f"u={u}, v={v}")
    nei[u].append(v)        
    nei[v].append(u)

#print(f"nei={nei}")

# problems' family:
max_starting_from = [1] * n # for every node v, this is meant to store the maximum length of a strictly increasing in vals path that starts from node v as its very first node.
best_of_bests = 1

# but, in order to achieve efficiency, we need to settle these n problems in proper order:
sorted_nodes=sorted([ (v,val[v]) for v in range(n) ], key=lambda x: -x[1]) # the - sign is because we want to consider first the nodes whose val is highest
for v,val_of_v in sorted_nodes: 
    for z in nei[v]:
        if val[z] > val_of_v:
            if 1+max_starting_from[z] > max_starting_from[v]:
                max_starting_from[v] = 1+max_starting_from[z]
                if max_starting_from[v] > best_of_bests:
                    best_of_bests = max_starting_from[v]
print(best_of_bests)
