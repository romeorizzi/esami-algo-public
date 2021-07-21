#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""Un template per la tua soluzione di hanoi_split
   Romeo Rizzi, 2021-06-20
"""
import sys
sys.setrecursionlimit(1000000)

t, N = map(int,input().split()) # problem type and number of disks
assert 0 <= t <= 1

def sposta_disco(i, peg_from, peg_to):
    print(f"sposta il disco {i} dal piolo {peg_from} al piolo {peg_to}")
    
if t == 0:
    print(42) # TO DO: stampa tù il numero corretto di mosse, ovviamente il template non lo fa per te
else:
    # TO DO (il template si limita a fornire la lista esplicita di mosse per N=3. A tè introdurre le procedure con la giusta logica in questo file
    sposta_disco(1,'A','B')
    sposta_disco(2,'A','C')
    sposta_disco(1,'B','C')
    sposta_disco(3,'A','B')
    sposta_disco(1,'C','B')
