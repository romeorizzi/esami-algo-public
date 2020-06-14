#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
sys.setrecursionlimit(100000)
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Template per soluzione in python per il problema online_budget_opt
Romeo Rizzi, 2019-07-28
"""

MAX_N = 1000000
MAX_VAL = 10

n, B0, t = map(int,input().split())
assert 1 <= n <= MAX_N
assert 0 <= B0

x = list(map(int,input().split()))
q = list(map(int,input().split()))
assert len(x) == n
assert len(q) == n
#print(x)
#print(q)

y = [B0] + [x[i] for i in range(n-1) ]

if t == 1:
    print( 42 )
else:
    print(" ".join(map(str, y)))


