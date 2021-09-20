#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**9)

n, m = map(int,input().strip().split())
#print(f"n={n}, m={m}")
val = list(map(int,input().strip().split()))
sorted_vals=sorted(val)
num_different_vals = 0
last_val = None
for val in sorted_vals:
    if val != last_val:
        num_different_vals += 1
        last_val = val
print(num_different_vals)
