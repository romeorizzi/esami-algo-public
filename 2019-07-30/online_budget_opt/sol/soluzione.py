#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
sys.setrecursionlimit(100000)
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione di online_budget_opt
   Autore: Romeo Rizzi
   Costo di questa soluzione: lineare.
   Descrizione: greedy dal fondo.
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

index_of_last_opportunity = [False] * n
max_so_far_q = -1
for i in reversed(range(n)):
    if q[i] > max_so_far_q:
        max_so_far_q = q[i]
        index_of_last_opportunity[i] = True # i is the index of a max so far of q from the right

B = B0
num_gemme = 0
y = [0] * n
for i in range(n):
    if index_of_last_opportunity[i]:
        y[i] = B
        num_gemme += y[i]*q[i]
        B = 0
    B += x[i]

if t == 1:
    print( num_gemme )
else:
    print(" ".join(map(str, y)))


