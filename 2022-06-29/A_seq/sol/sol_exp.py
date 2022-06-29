#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: sol_exp.py
 *  Soluzione esponenziale per il problema A_seq
 *  Romeo Rizzi, 2022-06-29
"""

import sys
import itertools

BASE = 10**9+7

# MAIN:
g, n = map(int,input().split()) # g in {1,2} sets the goal, n = length of the input sequence s
s = list(map(int,input().split()))
assert 1 <= g <= 2
assert 1 <= n
assert len(s) == n

set_of_indexes = set(range(n))   # the positions of elements in s are in [0,n-1]

def is_a_A_subseq(subset_of_indexes):
    #print(f"{subset_of_indexes=}")
    list_of_indexes = list(subset_of_indexes)
    list_of_indexes.sort()
    phase = "up"
    prev_index = list_of_indexes[0]
    for next_index in list_of_indexes[1:]:
        if s[next_index] == s[prev_index]:
            return False
        if phase == "up" and s[next_index] < s[prev_index]:
            phase = "down"
        elif phase == "down" and s[next_index] > s[prev_index]:
            return False
        prev_index = next_index 
    return True

max_len = 1
num_opt_sols = n
for next_target_size in range(2,n+1):
    #print(f"{next_target_size=}")
    sol_exists = False
    num_sols = 0
    for subset_of_indexes in itertools.combinations(set_of_indexes, next_target_size):
        if is_a_A_subseq(subset_of_indexes):
            sol_exists = True
            num_sols += 1
            num_sols %= BASE
            #print(f"{subset_of_indexes=}")
    if sol_exists:
        max_len = next_target_size
        num_opt_sols = num_sols
    else:
        break
    

if g == 1:
    print(max_len)
else:
    assert g == 2
    print(num_opt_sols)

