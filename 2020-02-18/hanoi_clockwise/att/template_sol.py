#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Un template per la tua soluzione di hanoi_clockwise
   Romeo Rizzi, 2020-02-18
"""
sys.setrecursionlimit(1000000)

#DEBUG = False
DEBUG = True

MAXN = 100000

t, N = map(int,input().split()) # probem type and number of disks
assert 0 <= t <= 1
assert 1 <= N <= MAXN
d = [None] + list(input()) # the final destinations of the disks (disks numbered from 1). In other words, d encodes the final configuration.
peg = [None] + ['A'] * N
assert len(d) == N+1
assert len(peg) == N+1
if DEBUG:
    print(f"problem type t={t}, number of disks N={N}, destinations' list d={d}, peg = {peg}")

def sposta_disco(i, peg_from, peg_to):
    assert peg[i] == peg_from
    print(f"sposta il disco {i} dal peg {peg_from} al peg {peg_to}")
    peg[i] = peg_to

def next_peg(peg):
    if peg == 'A':
        return 'B'
    if peg == 'B':
        return 'C'
    if peg == 'C':
        return 'A'

def sposta_intera_torre(n, peg_from, peg_to, peg_aux):
    """assume che tutti i dischi i <= n siano uno sopra l'altro in torre sul peg <peg_from>.
       Sposta questa intera torre sul peg <peg_to>, impiegano il minor numero di mosse possibile.
       Si assume che <peg_aux> indichi il terzo peg."""
    pass    

def smista_torre(n):
    """assume che tutti i dischi i <= n siano uno sopra l'altro in torre, tutti collocati su peg[n].
       Li consegna tutti alla loro destinazioni finali, come indicate in d."""
    pass

def num_steps_smista_torre(n):
    """Assume che tutti i dischi i <= n siano uno sopra l'altro in torre, tutti collocati su peg[n].
       Ritorna il numero di passi per smistare ciascun disco i <= n come specificato dalla destinazione d[i]""" 
    return 42

    
if t == 0:
    print(num_steps_smista_torre(N))
else:
    if d == [None] + ['B'] * N:
        sposta_intera_torre(N, 'A', 'B', 'C')
    else:
        smista_torre(N)
