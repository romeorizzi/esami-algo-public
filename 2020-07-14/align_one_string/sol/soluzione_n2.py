#!/usr/bin/env python3

import resource, sys
resource.setrlimit(resource.RLIMIT_STACK, (2**29,-1))
sys.setrecursionlimit(10**6)

INF = 1000000000

VIS = [[False for _ in range(1024)] for _ in range(1024)]
MEM = [[0 for _ in range(1024)] for _ in range(1024)]

def calcola(i, j):

    best = INF

    if i == len(A):
        if j == len(B): 
            return 0
        else:
            return best

    if j == len(B):
        return best

    if VIS[i][j]:
        return MEM[i][j]

    if A[i] == B[j]:
        best = min(best, calcola(i + 1, j + 1))

    k = i + 1

    while (k < len(A)) and (k - i < len(C)):
        best = min(best, calcola(k, j) + C[k - i])
        k += 1

    VIS[i][j] = True

    MEM[i][j] = best
    return MEM[i][j]


N, M, P = [int(x) for x in input().split()]

A = input().strip() + "+" # add a character at the end to allow final gap
B = input().strip() + "+"

C = [int(x) for x in input().split()]

result = calcola(0, 0)

if result >= INF:
    print(-1)
else:
    print(result) 
