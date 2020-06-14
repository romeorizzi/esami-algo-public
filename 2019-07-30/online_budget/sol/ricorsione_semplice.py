#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione di online_budget
   Autore: Romeo Rizzi
   Descrizione: ricorsione semplice. Algoritmo esponenziale.
"""

MAX_N = 1000000
MAX_VAL = 10

BIG_PRIME = 1000000007

n, B0 = map(int,input().split())
assert 1 <= n <= MAX_N
assert 0 <= B0

x = list(map(int,input().split()))
assert len(x) == n
#print(x)

def num_histories_from(i,B):
#    print(i,B)
    if i == n:
        return 1
    risp = 0
    for spesa_i in range(B+1):
        risp = (risp + num_histories_from(i+1, B -spesa_i +x[i] ) ) % BIG_PRIME
    return risp

print( num_histories_from(0,B0) )

