#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Un template per la tua soluzione di hanoi_equal_disks
   Romeo Rizzi, 2019-08-28
"""

#DEBUG = False
DEBUG = True

MAXN = 100000

t, N = map(int,input().split()) # probem type and number of disks
assert 0 <= t <= 1
assert 1 <= N <= MAXN
d = [None] + list(map(int,input().split())) # the diameters of the disks numbered form disk 1
assert len(d) == N+1
if DEBUG:
    print(f"problem type t={t}, number of disks N={N}, diameters' list d={d}")


def sposta_disco(i, piolo_from, piolo_to):
    print(f"sposta il disco {i} dal piolo {piolo_from} al piolo {piolo_to}")

    
if t == 0:
    print(1)
else:
    sposta_disco(1, 'A', 'B')
