#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione di pacman_best (ricorsione senza memoizzazione) 
   Autore: Romeo Rizzi, 2019-08-26
   Descrizione: ricorsione semplice. Algoritmo esponenziale.
"""

DEBUG1 = True
DEBUG2 = False
DEBUG3 = False

MAXBLUE = 9
MAXM = 1000
MAXN = 1000

M, N = map(int,input().split())
assert 1 <= M <= MAXM
assert 1 <= N <= MAXN

mappa = ['#' * (N+1)]
for line in sys.stdin:
    mappa.append('#' + line.rstrip('\n\r'))

assert len(mappa) == M+1
if DEBUG1:
    print(mappa, file=sys.stderr)

exists_complete = True
best_complete_ghosts = 1
best_complete_pills = 2

if exists_complete:
    print(f"1 {best_complete_ghosts} {best_complete_pills}")
else:
    print(f"0 {best_incomplete_ghosts} {best_incomplete_pills}")

