#!/usr/bin/env python2

import random
import sys

N = int(sys.argv[1])
T = sys.argv[2]

assert T in ("any", "distinct", "permutation")

if T in ("any", "distinct"):
    K, seed = map(int, sys.argv[3:])
    random.seed(seed)
    if T == "any":
        X = [random.randrange(1, K) for _ in range(N)]
    else:
        X = random.sample(range(1, K), k=N)
elif T == "permutation":
    seed, = map(int, sys.argv[3:])
    random.seed(seed)
    X = list(range(0, N))
random.shuffle(X)

print N
for x in X:
    print x
