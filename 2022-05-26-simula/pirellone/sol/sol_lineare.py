#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: sol_lineare.py
 *  Soluzione in python per pirellone
 *  Romeo Rizzi, 2022-05-25
"""

import sys

fin = open("input.txt","r")
m, n = map(int,fin.readline().split())
assert 1 <= m <= 500
assert 1 <= n <= 500
col_switches = list(map(int,fin.readline().split()))
row_switches = [0]
col_switches_complemented = [1-x for x in col_switches]
unsolvable = False
for i in range(m-1):
    row = list(map(int,fin.readline().split()))
    if row[0] == col_switches[0]:
        row_switches.append(0)
        if row != col_switches:
            unsolvable = True
    else:
        row_switches.append(1)
        if row != col_switches_complemented:
            unsolvable = True
with open("output.txt","w") as fout:
    if unsolvable:
        print(" ".join(['0']*m), file=fout)
        print(" ".join(['0']*n), file=fout)
    else:
        print(" ".join(map(str,row_switches)), file=fout)
        print(" ".join(map(str,col_switches)), file=fout)
