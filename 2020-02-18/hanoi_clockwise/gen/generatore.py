#!/usr/bin/env python2

from __future__ import print_function

import random
import sys

N_MAX = 100000
n_MAX = 20

t,N,nEff,nB,seed = map(int, sys.argv[1:])

assert 0 <= t <= 1
assert 1 <= N <= N_MAX
assert 0 <= nEff <= N
assert 0 <= nB <= nEff

print(t,N)
random.seed(seed)
print(''.join([random.choice('ABC') for _ in range(nEff-nB)]) + 'B' * nB + 'A' * (N-nEff) )
    
