#!/usr/bin/env python3

import sys
# import networkx as nx
import random

t = int(sys.argv[1])

n = int(sys.argv[2])
m = int(sys.argv[3])

pl = int(sys.argv[4])
pc = int(sys.argv[5])

s = int(sys.argv[6])

random.seed(s)

last = 0

def random_graph(n, m):
    global last
    last = 0

    def gen_edge(n):
        global last
        last1 = last
        last = random.randint(0, n - 1)
        return (last1, last)

    return [gen_edge(n) for _ in range(m)]

def random_bipartite(n, m):
    global last
    last = 0

    def gen_edge_bip(n):
        global last
        last1 = last
        if last < n // 2:
            last = random.randint(n//2, n - 1)
        else:
            last = random.randint(0, n//2 - 1)
        return (last1, last)



    return [gen_edge_bip(n) for _ in range(m)]

assert(n <= 100000)
assert(m <= 100000)

if t == 0:
    edges = random_graph(n, m)
elif t == 1:
    edges = random_bipartite(n, m)

elen = len(edges)
assert(elen == m)

print(n, elen, pl, pc)

for edge in edges:
    print(edge[0], edge[1], random.randint(0, 1000000))

