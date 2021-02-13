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

MEMO_vals = {}
    
def is_winning_pos(u,v):
    #print(f"called is_winning_pos(u={u},v={v})")
    if (u,v) in MEMO_vals.keys():
        return MEMO_vals[(u,v)]
    MEMO_vals[(u,v)] = True
    for u_next in out_nei1[u]:
        if not is_winning_pos(u_next,v):
           return True
    for v_next in out_nei2[v]:
        if not is_winning_pos(u, v_next):
           return True           
    MEMO_vals[(u,v)] = False
    return False
    
p = int(input())
#print(f"p={p}")
for _ in range(p):
    #print(f"u={u}, v={v}")
    u,v = map(int,input().strip('\n').split(' '))
    print(1 if is_winning_pos(u,v) else 0)
