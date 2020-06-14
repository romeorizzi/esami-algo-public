#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione lenta di hanoi_equal_disks
   Romeo Rizzi, 2019-08-28
"""

DEBUG = False
#DEBUG = True

MAXN = 100000

t, N = map(int,input().split()) # probem type and number of disks
assert 0 <= t <= 1
assert 1 <= N <= MAXN
d = [None] + list(map(int,input().split())) # the diameters of the disks numbered form disk 1
pole = [None] + ['A'] * N
assert len(d) == N+1
assert len(pole) == N+1
if DEBUG:
    print(f"problem type t={t}, number of disks N={N}, diameters' list d={d}, pole = {pole}")

moves_done = 0

def sposta_disco(i, piolo_from, piolo_to):
    assert pole[i] == piolo_from
    print(f"sposta il disco {i} dal piolo {piolo_from} al piolo {piolo_to}")
    pole[i] = piolo_to

def conta_spostamenti_disco(i, piolo_from, piolo_to):
    global moves_done
    assert pole[i] == piolo_from
    moves_done += 1
    pole[i] = piolo_to    

def sposta_torre(n, piolo_from, piolo_to, piolo_aux, basicActionOnDisk ):
    if n == 0:
        return
    nn = n
    while nn > 1 and d[nn] == d[nn-1]:
        nn -= 1
    sposta_torre(nn-1, piolo_from, piolo_aux, piolo_to, basicActionOnDisk)
    for i in range(nn,n+1):
        basicActionOnDisk(i, piolo_from, piolo_to)
    sposta_torre(nn-1, piolo_aux, piolo_to, piolo_from, basicActionOnDisk)
    
if t == 0:
    sposta_torre(N, 'A', 'B', 'C', conta_spostamenti_disco)
    print(moves_done)
else:
    sposta_torre(N, 'A', 'B', 'C', sposta_disco)
