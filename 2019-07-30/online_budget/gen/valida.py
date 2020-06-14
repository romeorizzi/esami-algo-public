#!/usr/bin/env python2

import limiti

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0])
    exit(1)


# 0            -> corretto
# altro numero -> non corretto
def run(f, st):
    n, B0 = map(int, f[0].split())
    if n > limiti.MAXN:
        return -1
    if n < 1:
        return -1
    if n != len(f[1].split()):
        return -1
    for x in map(int, f[1].split()):
        if x < limiti.MINVAL or x > limiti.MAXVAL:
            return -1
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
