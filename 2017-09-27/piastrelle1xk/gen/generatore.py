#!/usr/bin/env python2

import sys

N, K = map(int, sys.argv[1:])

assert 2 <= K <= 1000000

def max_n(N, K):
    R = [None for i in range(N+1)]

    for i in range(min(N,K)):
        R[i] = 1;

    for i in range(K,N+1):
        R[i] = R[i-1] + R[i-K]
        if R[i] > 1000000000:
            return i-1
    return N

if N == -1:
    N = max_n(1000000, K)
assert N == max_n(N, K)
assert 0 <= N <= 1000000

print N, K
