#!/usr/bin/env python2

"""
Parametri N1, M1, N2, M2, seed (interi).

Genera un grafo formato da una componente possibilmente ciclica
(con N1 nodi e M1 archi)
e una componente aciclica (con N2 nodi e M2 archi).
"""

import sys
import random

MAXN = 1000000
N1, M1, N2, M2, seed = map(int, sys.argv[1:])

random.seed(seed)

N = N1 + N2
M = M1 + M2

assert(2 <= N <= 1000000)
# cannot generate too dense graphs
assert(0 <= M1 <= N1*N/2)
assert(0 <= M2 <= N2*N2/4)

E = set()

while len(E) < M1:
    a, b = random.randint(0,N1-1), random.randint(0,N-1)
    if a == b:
        continue
    E.add((a, b))

while len(E) < M:
    a, b = random.randint(N1,N-1), random.randint(N1,N-1)
    if b <= a:
        continue
    E.add((a,b))

rename = list(range(N))
random.shuffle(rename)

print N, M
for a, b in E:
    print rename[a], rename[b]
