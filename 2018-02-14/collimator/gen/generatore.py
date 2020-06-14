#!/usr/bin/env python2

import random
import sys

MAXN = 1000000
MAX_VAL = 1000000

N, extrema_zero, max_jump, seed = map(int, sys.argv[1:])

random.seed(seed)

print N

values = [None] * N

values[0] = random.randint(0, 0 if extrema_zero else MAX_VAL)

for i in range(1,N):
    p = values[i-1];
    values[i] = random.randint(
        max([0, p-max_jump]),
        min([p+max_jump, N-1-i if extrema_zero else MAX_VAL]),
    )
print " ".join(str(v) for v in values)
