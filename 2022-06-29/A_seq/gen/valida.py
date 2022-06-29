#!/usr/bin/env python3

from limiti import *

import sys
import os


def usage():
    print("Usage: %s file_input.txt [subtask_number]" %
          sys.argv[0], file=sys.stderr)
    exit(1)


def run(f, st):
    assert len(f) <= 3
    g, n = map(int, f[0].split())
    assert 1 <= g <= 2
    assert 1 <= n <= MAXN

    s = list(map(int, f[1].split()))
    assert len(s) == n
    for ele in s:
        assert 0 <= ele <= MAX_VAL


if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    run(f, st)
