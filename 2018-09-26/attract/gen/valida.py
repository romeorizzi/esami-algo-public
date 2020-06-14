#!/usr/bin/env python2
# Usare pypy solo quando necessario. La compilazione richiede tempo e viene ricompilato per ogni testcase.

from limiti import *

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0])
    exit(1)


# 0            -> corretto
# altro numero -> non corretto
# per testare la correttezza dell'input, usate assert()
def run(f, st):
    N, M = map(int, f[0].split())
    assert(1<=N<=MAXN)
    assert(N<=M<=MAXM)
    print len(f), M
    assert(len(f) == M+2)
    assert(len(f[1].split()) == N)
    edges = set()
    sources = set()
    for r in f[2:]:
        a, b = map(int, r.split())
        assert(a!=b)
        assert(0<=a<N)
        assert(0<=b<N)
        edges.add((a,b))
        sources.add((a))
    assert(len(edges) == M)
    assert(len(sources) == N)
    return 0

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
