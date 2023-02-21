#!/usr/bin/env python3

import random
import sys

MAXN = 1000000
N, max_val, seed = map(int, sys.argv[1:])
assert (1 <= N <= MAXN)

random.seed(seed)

print(N)
for i in range(N):
    print(random.randint(0, max_val+1), end=" ")
print()
