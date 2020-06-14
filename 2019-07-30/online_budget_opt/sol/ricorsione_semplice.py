#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione di online_budget_opt
   Autore: Romeo Rizzi
   Descrizione: ricorsione semplice. Algoritmo esponenziale.
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

def max_from(i,B):
#    print(i,B)
    if i == n-1:
        return B*q[i]
    risp = 0
    for spesa_i in range(B+1):
        risp = max(risp, spesa_i*q[i] + max_from(i+1, B -spesa_i +x[i] ) )
    return risp

promessa = max_from(0,B0)
if t == 1:
    print( promessa )
else:
    assert t == 2
    B = B0
    y = [0] * n
    for i in range(n-1):
        while y[i]*q[i] + max_from(i+1, B -y[i] +x[i] ) < promessa:
            y[i] += 1
        promessa -= y[i]*q[i]
        B = B - y[i] + x[i]
    y[n-1] = B
    print(" ".join(map(str, y)))
    promessa -= y[n-1]*q[n-1]
    assert promessa == 0
