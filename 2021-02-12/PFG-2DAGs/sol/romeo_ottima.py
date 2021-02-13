#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**9)

n1, m1 = map(int,input().strip('\n').split(' '))
#print(f"n1={n1}, m1={m1}")
out_nei1 = [ [] for v in range(n1) ]
for _ in range(m1):
    u,v = map(int,input().strip('\n').split(' '))
    #print(f"u={u}, v={v}")
    out_nei1[u].append(v)        

n2, m2 = map(int,input().strip('\n').split(' '))
#print(f"n2={n2}, m2={m2}")
out_nei2 = [ [] for v in range(n2) ]
for _ in range(m2):
    u,v = map(int,input().strip('\n').split(' '))
    #print(f"u={u}, v={v}")
    out_nei2[u].append(v)        

def dfs(h, v, n, out_nei, grundy): # the recursion height h is present only to facilitate debugging
    assert h <= n
    #print(f"called dfs(h={h}, v={v}, n={n}, out_nei={out_nei}, grundy={grundy})")
    if grundy[v] == None:
        if len(out_nei) == 0:
            grundy[v] = 0
        else:
            seen_vals = {}
            for u in out_nei[v]:
                seen_vals[dfs(h+1, u, n, out_nei, grundy)] = True
            v_val = 0
            while v_val in seen_vals.keys():
                v_val += 1
            grundy[v] = v_val
    #print(f"grundy({v})={grundy[v]})")
    return grundy[v]

grundy1 = [ None for v in range(n1) ]
for v in range(n1):
    if grundy1[v] == None:
        dfs(0, v, n1, out_nei1, grundy1)
#print(f"grundy1={grundy1}")
        
grundy2 = [ None for v in range(n2) ]
for v in range(n2):
    if grundy2[v] == None:
        dfs(0, v, n2, out_nei2, grundy2)
#print(f"grundy2={grundy2}")

p = int(input())
#print(f"p={p}")

for _ in range(p):
    u,v = map(int,input().strip('\n').split(' '))
    #print(f"u={u}, v={v}, grundy1[u]={grundy1[u]}, grundy2[v]={grundy2[v]}")
    print(0 if grundy1[u] == grundy2[v] else 1)
