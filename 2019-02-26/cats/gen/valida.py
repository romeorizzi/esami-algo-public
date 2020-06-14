#!/usr/bin/env python3

from limiti import *

import sys
import os


def usage():
    print("Usage: %s file_input.txt [subtask_number]" %
          sys.argv[0], file=sys.stderr)
    exit(1)


def run(f, st):
    assert(len(f) == 3)
    Nm, Nf = map(int, f[0].split())
    assert(1 <= Nm <= MAXN)
    assert(1 <= Nf <= MAXN)

    males = list(map(int, f[1].split()))
    females = list(map(int, f[2].split()))

    assert(len(males) == Nm)
    assert(len(females) == Nf)

    assert(all(0 <= m <= MAXV for m in males))
    assert(all(0 <= f <= MAXV for f in females))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    run(f, st)
