#!/usr/bin/env python3
# -*- coding: latin-1 -*-

n = int(input())
val = list(map(int,input().split()))
assert len(val) == n

dyn = [0,0,0]
for i in reversed(range(n)):
    dyn[i%3] = val[i] + max(dyn[(i+2)%3], dyn[i%3])

print(dyn[0])

    
