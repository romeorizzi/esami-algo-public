#!/usr/bin/python3
import sys 
sys.setrecursionlimit(10**5)

n, m = map(int,sys.stdin.readline().split())
print(f"n={n}, m={m}")
w = list(map(int,sys.stdin.readline().split()))
print(f"node wights={w}")
for _ in range(m):
    u,v = map(int,sys.stdin.readline().split())
    print(f"u={u}, v={v}")
