#!/usr/bin/env python2

from __future__ import print_function

import random
import sys

N_MAX = 100000
n_MAX = 30

t,N,n,seed = map(int, sys.argv[1:])

assert 0 <= t <= 1
assert 1 <= N <= N_MAX
assert 1 <= n <= n_MAX

print(t,N)
random.seed(seed)

block_size = [1+N//n] *(N%n) + [N//n] *(n-N%n)
#print(block_size)

d = int(random.choice('123456789'))
for bs in block_size:
    for _ in range(bs):
        print(d, end=' ')
    d += int(random.choice('123456789'))
print()
