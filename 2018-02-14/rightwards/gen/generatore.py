#!/usr/bin/env python2

import random
import sys

M, N, min_val, max_val, seed = map(int, sys.argv[1:])

random.seed(seed)

print M, N
for i in range(M):
    print " ".join([str(random.randint(min_val, max_val)) for j in range(N)])
