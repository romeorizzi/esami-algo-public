#!/usr/bin/env python2

from __future__ import print_function

import random
import sys

M, N = map(int, sys.argv[1:3])

M_MAX = 500
N_MAX = 500

assert 2 <= M <= M_MAX
assert 2 <= N <= N_MAX

wall_p, ghost_p, pill_p = map(float, sys.argv[3:6])
seed = int(sys.argv[6])

random.seed(seed)

def random_type():
    p = random.random()

    if p <= wall_p:
        return '#'
    p -= wall_p
    if p <= ghost_p:
        return '*'
    p -= ghost_p
    if p <= pill_p:
        return random.choice('12345')
    return '+'



print(M, N)
print(*(['+'] * N), sep='')
for i in range(M-1):
    print(*([random_type() for j in range(N-1)] + ['+']), sep='')
