#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: soluzione.py
 *  Soluzione di riferimento per hanoi_with_split_merge
 *  Romeo Rizzi, 2021-09-17
"""

import sys

sys.setrecursionlimit(1000000)

t, t1, N = map(int,input().split()) # problem types (t=0 count, t=1 lists); (t1=0 classic, t1=1 with balanced split/merge, t1=2with all split/merge), and number of disks
assert 0 <= t <= 1
assert 0 <= t1 <= 2

def sposta_disco(i, peg_from, peg_to):
    global moves_counter
    moves_counter += 1
    print(f"sposta il disco {i} dal piolo {peg_from} al piolo {peg_to}")

def sposta_torre_classic(n, peg_from, peg_to, peg_aux):
    """assume che tutti i dischi i <= n siano uno sopra l'altro in torre sul peg <peg_from>.
       Sposta questa intera torre sul peg <peg_to>, impiegando il minor numero di mosse possibile.
       Si assume che <peg_aux> indichi il terzo peg."""
    if n == 0:
        return
    else:
        sposta_torre_classic(n-1, peg_from, peg_aux, peg_to)
        sposta_disco(n, peg_from, peg_to)
        sposta_torre_classic(n-1, peg_aux, peg_to, peg_from)

def split_dal_disco(i, peg_from, peg_dest1, peg_dest2):
    global moves_counter
    moves_counter += 1
    print(f"split il piolo {peg_from}, dal disco {i}, sui pioli {peg_dest1} e {peg_dest2}")

def merge_dal_disco(i, peg_dest, peg_from1, peg_from2):
    global moves_counter
    moves_counter += 1
    print(f"merge sul piolo {peg_dest}, dal disco {i} del piolo {peg_from1} e dal piolo {peg_from2}")

def sposta_torre_with_balanced_moves(n, peg_from, peg_to, peg_aux):
    """assume che tutti i dischi i <= n siano uno sopra l'altro in torre sul peg <peg_from>.
       Sposta questa intera torre sul peg <peg_to>, secondo l'unica soluzione ottima.
       Si assume che <peg_aux> indichi il terzo peg."""
    if n == 0:
        return
    if n%2==1:
        sposta_torre_with_balanced_moves(n-1, peg_from, peg_aux, peg_to)
        sposta_disco(n, peg_from, peg_to)
        sposta_torre_with_balanced_moves(n-1, peg_aux, peg_to, peg_from)
    else: # n%2==0 (even number of disks)
        split_dal_disco(n, peg_from, peg_to, peg_aux)
        if n == 2:
            sposta_disco(n-1, peg_aux, peg_to)
        else: # n >= 4:
            merge_dal_disco(n-2, peg_from, peg_to, peg_aux)
            sposta_disco(n-1, peg_aux, peg_to)
            sposta_torre_with_balanced_moves(n-2, peg_from, peg_to, peg_aux)            

def sposta_torre_with_all_moves(n, peg_from, peg_to, peg_aux):
    """assume che tutti i dischi i <= n siano uno sopra l'altro in torre sul peg <peg_from>.
       Sposta questa intera torre sul peg <peg_to>, secondo l'unica soluzione ottima.
       Si assume che <peg_aux> indichi il terzo peg."""
    if n == 0:
        return
    if n == 1:
        sposta_disco(1, peg_from, peg_to)
    else:
        split_dal_disco(n, peg_from, peg_to, peg_aux)
        if n == 2:
            sposta_disco(n-1, peg_aux, peg_to)
        elif n <= 4:
            sposta_disco(n-2, peg_to, peg_from)
            merge_dal_disco(n-1, peg_to, peg_aux, peg_from)
        else: # n >= 4:
            merge_dal_disco(n-2, peg_from, peg_to, peg_aux)
            sposta_disco(n-1, peg_aux, peg_to)
            sposta_torre_with_all_moves(n-2, peg_from, peg_to, peg_aux)

def num_moves(t1,n):
    #print(f"called num_moves(t1={t1},n={n})")
    assert n >= 0
    if t1==0:
        return 2**n -1
    if n <= 2:
        return n
    if t1==1:
        if n%2==1:
            return 2*num_moves(t1,n-1) +1
        else:
            return 3+num_moves(t1,n-2)
    if t1==2:
        if n<=4:
            return 3
        return 3+num_moves(t1,n-2)
    

    
          
if t == 0:
    print(num_moves(t1,N))
elif t == 1:
    moves_counter = 0
    if t1==0:
        sposta_torre_classic(N, 'A', 'C', 'B')
        assert moves_counter == num_moves(t1,N)
    elif t1==1:
        sposta_torre_with_balanced_moves(N, 'A', 'C', 'B')
        assert moves_counter == num_moves(t1,N)
    elif t1==2:
        sposta_torre_with_all_moves(N, 'A', 'C', 'B')
        assert moves_counter == num_moves(t1,N)
