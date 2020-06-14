#!/usr/bin/env python2

import sys
fin = open(sys.argv[1])

N = int(fin.readline().strip())

assert 1 <= N <= 100000

X = [
    int(fin.readline().strip())
    for _ in range(N)
]

assert all(0 <= x <= 100000 for x in X)
