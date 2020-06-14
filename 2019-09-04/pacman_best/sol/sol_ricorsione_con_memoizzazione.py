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

DEBUG1 = False
DEBUG2 = False
DEBUG3 = False

MAXBLUE = 9
MAXM = 100
MAXN = 100

M, N = map(int,input().split())
assert 1 <= M <= MAXM
assert 1 <= N <= MAXN

mappa = ['#' * (N+1)]
for line in sys.stdin:
    mappa.append('#' + line.rstrip('\n\r'))

assert len(mappa) == M+1
if DEBUG1:
    print(mappa, file=sys.stderr)

memo_risp = [ [ [None] * (MAXBLUE+1) for c in range(N+2)] for r in range(M+2)] 
    
def ric(r,c,b):
    """returns the best value of a path starting from cell mappa[1][1] and arriving to cell mappa[i][j] with b units of residual blue (can still eat b ghosts after leaving cell mappa[i][j] without encountering any pills). This value is a triple: first comes whether a path exists, then we maximize the number of ghosts captured, then we minimize the number of pill cells visited."""
    if DEBUG2:
        print(f"called with r={r},c={c},b={b}. Mappa[{r}][{c}]='{mappa[r][c]}'", file=sys.stderr)
    if r==1 and c==1:
        if mappa[1][1] == '+' and b == 0:
            return [True, 0, 0]
        if b == ord(mappa[1][1])-ord('0'):
            return [True, 0, 1]
        return [False, 0, MAXM+MAXN]
    if memo_risp[r][c][b] != None:
        return memo_risp[r][c][b]
    memo_risp[r][c][b] = [False, 0, MAXM+MAXN]
    if mappa[r][c] == '#':
        return memo_risp[r][c][b]
    if mappa[r][c] == '+':
        if b < MAXBLUE:
            risp_left = ric(r,c-1,b+1);
            risp_up = ric(r-1,c,b+1);
            if risp_left[0]:
                memo_risp[r][c][b][0] = True
                memo_risp[r][c][b][1] = risp_left[1]
                memo_risp[r][c][b][2] = risp_left[2]
            if risp_up[0]:
                memo_risp[r][c][b][0] = True
                if risp_up[1] >= memo_risp[r][c][b][1] and ( risp_up[1] > memo_risp[r][c][b][1] or risp_up[2] < memo_risp[r][c][b][2] ):	
                    memo_risp[r][c][b][1] = risp_up[1]
                    memo_risp[r][c][b][2] = risp_up[2]
        if b == 0:
            risp_left2 = ric(r,c-1,0);
            risp_up2 = ric(r-1,c,0);
            if risp_left2[0]:
                memo_risp[r][c][b][0] = True
                if risp_left2[1] >= memo_risp[r][c][b][1] and ( risp_left2[1] > memo_risp[r][c][b][1] or risp_left2[2] < memo_risp[r][c][b][2] ):	
                    memo_risp[r][c][b][1] = risp_left2[1]
                    memo_risp[r][c][b][2] = risp_left2[2]
            if risp_up2[0]:
                memo_risp[r][c][b][0] = True
                if risp_up2[1] >= memo_risp[r][c][b][1] and ( risp_up2[1] > memo_risp[r][c][b][1] or risp_up2[2] < memo_risp[r][c][b][2] ):	
                    memo_risp[r][c][b][1] = risp_up2[1]
                    memo_risp[r][c][b][2] = risp_up2[2]

    elif mappa[r][c] == '*':
        if b < MAXBLUE:
            risp_left = ric(r,c-1,b+1);
            risp_up = ric(r-1,c,b+1);
            if risp_left[0]:
                memo_risp[r][c][b][0] = True
                memo_risp[r][c][b][1] = risp_left[1] +1
                memo_risp[r][c][b][2] = risp_left[2]
            if risp_up[0]:
                memo_risp[r][c][b][0] = True
                if risp_up[1] +1 >= memo_risp[r][c][b][1] and ( risp_up[1] +1 > memo_risp[r][c][b][1] or risp_up[2] < memo_risp[r][c][b][2] ):	
                    memo_risp[r][c][b][1] = risp_up[1] +1
                    memo_risp[r][c][b][2] = risp_up[2] 
    else:
        blue = ord(mappa[r][c]) - ord('0')
        if blue < b < MAXBLUE:
            risp_left = ric(r,c-1,b+1);
            risp_up = ric(r-1,c,b+1);
            if risp_left[0]:
                memo_risp[r][c][b][0] = True
                memo_risp[r][c][b][1] = risp_left[1]
                memo_risp[r][c][b][2] = risp_left[2] +1
            if risp_up[0]:
                memo_risp[r][c][b][0] = True
                if risp_up[1] >= memo_risp[r][c][b][1] and ( risp_up[1] > memo_risp[r][c][b][1] or risp_up[2] +1 < memo_risp[r][c][b][2] ):	
                    memo_risp[r][c][b][1] = risp_up[1]
                    memo_risp[r][c][b][2] = risp_up[2] +1
        # if b < blue then no path exists, as alrady set by default
        if b == blue:
            for bb in range(blue+2):
                if bb <= MAXBLUE:
                    risp_left = ric(r,c-1,bb);
                    risp_up = ric(r-1,c,bb);
                    if risp_left[0]:
                        memo_risp[r][c][b][0] = True
                        if risp_left[1] >= memo_risp[r][c][b][1] and ( risp_left[1] > memo_risp[r][c][b][1] or risp_left[2] +1 < memo_risp[r][c][b][2] ):
                            memo_risp[r][c][b][1] = risp_left[1]
                            memo_risp[r][c][b][2] = risp_left[2] +1
                    if risp_up[0]:
                        memo_risp[r][c][b][0] = True
                        if risp_up[1] >= memo_risp[r][c][b][1] and ( risp_up[1] > memo_risp[r][c][b][1] or risp_up[2] +1 < memo_risp[r][c][b][2] ):	
                            memo_risp[r][c][b][1] = risp_up[1]
                            memo_risp[r][c][b][2] = risp_up[2] +1
    return memo_risp[r][c][b]
  

exists_complete = False
best_complete_ghosts = 0
best_complete_pills  = MAXM+MAXN 
best_incomplete_ghosts = 0
best_incomplete_pills  = MAXM+MAXN 
for r in range(1,M+1):
    for c in range(1,N+1):
        for b in range(MAXBLUE+1):
            if DEBUG3:
                print(f"now calling ric(r={r}, c={c}, b={b})", file=sys.stderr)
            risp = ric(r,c,b)
            if DEBUG2:
                if risp[0]:
                    print(f"got answer for [r={r}, c={c}, b={b}]: exists = {risp[0]}, Max_ghosts = {risp[1]}, min_pills = {risp[2]}", file=sys.stderr)
                else:
                    print(f"got answer for [r={r}, c={c}, b={b}]: exists = {risp[0]}", file=sys.stderr)

            if risp[0]:
                if r==M and c==N:
                    exists_complete = True
                    if risp[1] >= best_complete_ghosts and ( risp[1] > best_complete_ghosts or risp[2] < best_complete_pills):
                       best_complete_ghosts = risp[1]
                       best_complete_pills  = risp[2]
                else:
                    if risp[1] >= best_incomplete_ghosts and ( risp[1] > best_incomplete_ghosts or risp[2] < best_incomplete_pills):
                        best_incomplete_ghosts = risp[1]
                        best_incomplete_pills  = risp[2]
                    
if exists_complete:
    print(f"1 {best_complete_ghosts} {best_complete_pills}")
else:
    print(f"0 {best_incomplete_ghosts} {best_incomplete_pills}")

