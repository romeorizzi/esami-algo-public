#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""Un template per la tua soluzione di hanoi_with_split_merge
   Romeo Rizzi, 2021-09-17
"""
import sys
sys.setrecursionlimit(1000000)

t, t1, N = map(int,input().split()) # problem types (t=0 count, t=1 lists); (t1=0 classic, t1=1 with balanced split/merge, t1=2with all split/merge), and number of disks
assert 0 <= t <= 1
assert 0 <= t1 <= 2

def sposta_disco(i, peg_from, peg_to):
    print(f"sposta il disco {i} dal piolo {peg_from} al piolo {peg_to}")

def split_dal_disco(i, peg_from, peg_dest1, peg_dest2):
    print(f"split il piolo {peg_from}, dal disco {i}, sui pioli {peg_dest1} e {peg_dest2}")

def merge_dal_disco(i, peg_dest, peg_from1, peg_from2):
    print(f"merge sul piolo {peg_dest}, dal disco {i} del piolo {peg_from1} e dal piolo {peg_from2}")


    
if t == 0:
    print(42) # TO DO: stampa tù il numero corretto di mosse, ovviamente il template non lo fa per te
else:
    # TO DO (il template si limita a fornire la lista esplicita di mosse per N=3. A tè introdurre le procedure con la giusta logica in questo file
    sposta_disco(1,'A','B')
    sposta_disco(2,'A','C')
    sposta_disco(1,'B','C')
    sposta_disco(3,'A','B')
    sposta_disco(1,'C','B')
