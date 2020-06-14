#!/usr/bin/env python2

import random
import sys

MAXN = 1000000
# H = altezza massima
N, H, seed = map(int, sys.argv[1:])
assert (1 <= N <= MAXN)
assert (2 <= H <= MAXN)

random.seed(seed)

print N
for i in range(N):
    h = 1
    while random.random() < 0.25:
        h += 1
    print min(h,H),
print
