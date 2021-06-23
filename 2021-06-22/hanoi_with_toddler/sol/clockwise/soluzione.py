#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione di hanoi_clockwise
   Romeo Rizzi, 2020-02-18
"""
sys.setrecursionlimit(1000000)

DEBUG = False
#DEBUG = True

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
    if n == 0:
        return
    if peg_to == next_peg(peg_from):
        sposta_intera_torre(n-1, peg_from, peg_aux, peg_to)
        sposta_disco(n, peg_from, peg_to)
        sposta_intera_torre(n-1, peg_aux, peg_to, peg_from)
    else:
        sposta_intera_torre(n-1, peg_from, peg_to, peg_aux)
        sposta_disco(n, peg_from, peg_aux)
        sposta_intera_torre(n-1, peg_to, peg_from, peg_aux)
        sposta_disco(n, peg_aux, peg_to)
        sposta_intera_torre(n-1, peg_from, peg_to, peg_aux)

def num_steps_sposta_intera_torre_by_1(n):
    """ritorna il numero di passi per spostare un'intera torre quando peg_to == next_peg(peg_from)""" 
    if n == 0:
        return 0
    return 1 + 2*num_steps_sposta_intera_torre_by_2(n-1)

memo_num2 = [0] + [None] * 30
def num_steps_sposta_intera_torre_by_2(n):
    """ritorna il numero di passi per spostare un'intera torre quando peg_to == next_peg(next_peg(peg_from))"""
    if memo_num2[n] == None:
        memo_num2[n] = 2 + 2*num_steps_sposta_intera_torre_by_2(n-1) + num_steps_sposta_intera_torre_by_1(n-1)
    return memo_num2[n]

        
def smista_torre(n):
    """assume che tutti i dischi i <= n siano uno sopra l'altro in torre, tutti collocati su peg[n].
       Li consegna tutti alla loro destinazioni finali, come indicate in d."""
    if n == 0:
        return
    if peg[n] == d[n]:
        smista_torre(n-1)
        return
    sposta_intera_torre(n-1, peg[n-1], next_peg(next_peg(peg[n])), next_peg(peg[n]))
    sposta_disco(n, peg[n], next_peg(peg[n]))
    if peg[n] == d[n]:
        smista_torre(n-1)
        return
    sposta_intera_torre(n-1, peg[n-1], next_peg(peg[n-1]), next_peg(next_peg(peg[n-1])))
    sposta_disco(n, peg[n], d[n])
    smista_torre(n-1)

def num_steps_smista_torre(n):
    """Assume che tutti i dischi i <= n siano uno sopra l'altro in torre, tutti collocati su peg[n].
       Ritorna il numero di passi per smistare ciascun disco i <= n come specificato dalla destinazione d[i]""" 
    if n == 0:
        return 0
    if peg[n] == d[n]:
        return num_steps_smista_torre(n-1)
    risp = 1 + num_steps_sposta_intera_torre_by_2(n-1)
    if next_peg(peg[n]) != d[n]:
        risp += 1 + num_steps_sposta_intera_torre_by_1(n-1)
    peg[n] = d[n]
    for i in range(1,n):
        peg[i] = next_peg(peg[n])
    return risp + num_steps_smista_torre(n-1)
    
        
if t == 0:
    print(num_steps_smista_torre(N))
else:
    if d == [None] + ['B'] * N:
        sposta_intera_torre(N, 'A', 'B', 'C')
    else:
        smista_torre(N)
