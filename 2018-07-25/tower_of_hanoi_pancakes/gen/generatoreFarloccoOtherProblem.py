#!/usr/bin/env python2

import random
import sys

MAXN = 1000000
N, max_val, forced_max, seed = map(int, sys.argv[1:])
assert (1 <= N <= MAXN)

random.seed(seed)

print N
for i in range(N):
    print random.randint(0, 10),
print

for i in range(N):
    if forced_max > 0:
        print max_val,
    else:
        print random.randint(0, max_val),
print
