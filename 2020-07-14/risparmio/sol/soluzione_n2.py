#!/usr/bin/env python3
A = [0] * 100000

N, M = [int(x) for x in input().split(' ')]

for i in range(M):
    op = [int(x) for x in input().split(' ')]
    t = op[0]

    if t == 1:
        x = op[1]
        A[x] ^= 1
    elif t == 2:
        x = op[1]
        y = op[2]
        
        totint = 0
        for j in range(x, y+1):
            if A[j] and (j == x or not A[j-1]):
                totint += 1
                
        print(totint)
