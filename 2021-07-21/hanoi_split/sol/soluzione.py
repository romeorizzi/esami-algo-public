#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: soluzione.py
 *  Soluzione di riferimento per hanoi_split
 *  Romeo Rizzi, 2021-07-19
"""

import sys

sys.setrecursionlimit(1000000)

t, N = map(int,input().split()) # problem type and number of disks
assert 0 <= t <= 1

dest_peg=['C','B']   #even disks should go to peg 'C', odd disks should go to peg 'B'

def sposta_disco(i, peg_from, peg_to):
    print(f"sposta il disco {i} dal piolo {peg_from} al piolo {peg_to}")

def sposta_intera_torre(n, peg_from, peg_to, peg_aux):
    """assume che tutti i dischi i <= n siano uno sopra l'altro in torre sul peg <peg_from>.
       Sposta questa intera torre sul peg <peg_to>, impiegando il minor numero di mosse possibile.
       Si assume che <peg_aux> indichi il terzo peg."""
    if n == 0:
        return
    else:
        sposta_intera_torre(n-1, peg_from, peg_aux, peg_to)
        sposta_disco(n, peg_from, peg_to)
        sposta_intera_torre(n-1, peg_aux, peg_to, peg_from)

def third_peg(peg1,peg2):
    return chr(ord('A')+ (3 - (ord(peg1)-ord('A')) - (ord(peg2)-ord('A')) ) )


def num_moves_to_move_a_whole_tower(n):
    """ritorna il numero di passi per spostare un'intera torre da un piolo ad un altro""" 
    if n == 0:
        return 0
    return 1 + 2*num_moves_to_move_a_whole_tower(n-1)

        
def split_intera_torre(n, peg_from, truly_act):
    """assume che tutti i dischi i <= n siano uno sopra l'altro in torre sul piolo peg_from.
       Li consegna tutti alla loro rispettive destinazioni finali. Se truly_act==true allora stampa effettivamente la lista delle mosse da compiere, altrimenti si limita a restituirne il numero"""
    if n == 0:
        return 0
    if peg_from==dest_peg[n%2]:
        return split_intera_torre(n-1, peg_from, truly_act)
    peg_aux = third_peg(peg_from, dest_peg[n%2])
    if truly_act:
        sposta_intera_torre(n-1, peg_from, peg_aux, dest_peg[n%2])
        sposta_disco(n, peg_from, dest_peg[n%2])
        return num_moves_to_move_a_whole_tower(n-1) +1 + split_intera_torre(n-1, peg_aux, truly_act)
    else:
        return num_moves_to_move_a_whole_tower(n-1) +1 +split_intera_torre(n-1, peg_aux, truly_act)

          
if t == 0:
    print(split_intera_torre(N, 'A', False))
else:
    split_intera_torre(N, 'A', True)
