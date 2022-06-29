#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: sol_lineare
 *  Soluzione di riferimento per il problema k_up_1_down_seq
 *  Romeo Rizzi, 2022-02-02
"""

import sys
sys.setrecursionlimit(10**6)

BASE = 10**9+7

# THE RECURSIVE SOLUTION PROCEDURES
    
def list_sequences(n):
    for r in range(num_sequences(n)):
        print(unrank(n,r))

MEMO_num_seq = {}
def num_sequences(n,first_val=0): # Nella nostra famiglia di problemi, il primo valore della sequenza può essere anche diverso da 0. (Abbiamo generalizzato il problema per trovare facile chiusura rispetto ad induzione.)
    assert n >= 1
    global MEMO_num_seq
    #print(f"{n=},  {first_val=}")
    if first_val < 0 or first_val >= n:
        return 0
    if n == 1:
        return 1
    if (n,first_val) not in MEMO_num_seq:
        MEMO_num_seq[(n,first_val)] = (
        num_sequences(n-1,first_val) +    # Case 1: primi due elementi uguali
        num_sequences(n-1,first_val -1) + # Case 2: secondo elemento cala di 1
        num_sequences(n-1,first_val +k)   # Case 3: secondo elemento cresce di k
           ) % BASE
    return MEMO_num_seq[(n,first_val)]


def unrank(n,r,first_val=0):
    #print(f"{n=}, {r=}, {first_val=}", file=sys.stderr)
    assert 0 <= r
    assert n >= 1
    assert first_val >= 0
    if n == 1:
        assert first_val == 0
        return "0"
    if r < num_sequences(n-1,first_val -1):
        #print("first_val -1", file=sys.stderr)
        return str(first_val) + " "+ unrank(n-1,r,first_val -1)
    r = r - num_sequences(n-1,first_val -1)
    if r < num_sequences(n-1,first_val):
        #print("first_val", file=sys.stderr)
        return str(first_val) + " "+ unrank(n-1,r,first_val)
    r = r - num_sequences(n-1,first_val)
    #print("first_val +k", file=sys.stderr)
    return str(first_val) + " "+ unrank(n-1,r,first_val +k)

def rank(n,s):
    #print(f"{n=}, {s=}", file=sys.stderr)
    assert s[0] >= 0
    if n == 1:
        assert s[0] == 0
        return 0
    r = 0
    if s[1] == s[0] -1:
        return r + rank(n-1,s[1:])
    r += num_sequences(n-1,s[0] -1)
    if s[1] == s[0]:
        return r + rank(n-1,s[1:])
    r += num_sequences(n-1,s[0])
    return r + rank(n-1,s[1:])

# MAIN:
g, n, k = map(int,input().split()) # g in {1,2,3,4} sets the goal, n = length of the n,k-sequence
assert 1 <= g <= 4
assert 1 <= n
assert 1 <= k

if g == 1:
    print(num_sequences(n))
elif g == 2:
    r = int(input())
    print(unrank(n,r))
elif g == 3:
    s = list(map(int,input().split()))
    print(rank(n,s))
else:
    assert g == 4
    list_sequences(n)

