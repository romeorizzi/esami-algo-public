#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**9)

MAXN=100000
MAXM=200000
N, M = map(int,input().strip().split())
assert 0 <= N <= MAXN
assert 0 <= M <= MAXM
#print(f"{N=}, {M=}")
for i in range(M):
    u,v = map(int,input().strip().split())
    assert 0 <= u < N
    assert 0 <= v < N
    #print(f"message={u}, ship={v}")
    
print(-1)
exit(0)
