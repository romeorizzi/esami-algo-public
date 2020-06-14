#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
sys.setrecursionlimit(100000)
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione di online_budget
   Autore: Romeo Rizzi
   Descrizione: ricorsione con memoizzazione.
"""

MAX_N = 500
MAX_VAL = 10

BIG_PRIME = 1000000007

n, B0 = map(int,input().split())
assert 1 <= n <= MAX_N
assert 0 <= B0

x = list(map(int,input().split()))
assert len(x) == n
#print(x)

risp = [ [None] * (B0 + MAX_VAL*n +1) for _ in range(n+1) ]

def num_histories_from(i,B):
#    print(i,B,risp[i][B])
#    print(risp)
    if risp[i][B] == None:
        if i == n:
            risp[i][B] = 1
        else:
            risp[i][B] = 0
            for spesa_i in range(B+1):
                risp[i][B] = (risp[i][B] + num_histories_from(i+1, B -spesa_i +x[i] ) ) % BIG_PRIME
    return risp[i][B]

print( num_histories_from(0,B0) )

