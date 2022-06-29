#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: sol_quadratica.py
 *  Soluzione quadratica per il problema A_seq
 *  Romeo Rizzi, 2022-06-29
"""

import sys

BASE = 10**9+7

# MAIN:
g, n = map(int,input().split()) # g in {1,2} sets the goal, n = length of the input sequence s
s = list(map(int,input().split()))
assert 1 <= g <= 2
assert 1 <= n
assert len(s) == n

# the positions of elements in s are in [0,n-1]
longest_increasing_ending_with_element_at_pos = [1] * n
longest_decreasing_starting_with_element_at_pos = [1] * n
num_longest_increasing_ending_with_element_at_pos = [1] * n
num_longest_decreasing_starting_with_element_at_pos = [1] * n

for ele,pos in zip(s[1:],range(1,n)):
    for prev_pos in range(pos):
        if s[prev_pos] < ele:
            if longest_increasing_ending_with_element_at_pos[pos] < 1+longest_increasing_ending_with_element_at_pos[prev_pos]:
                longest_increasing_ending_with_element_at_pos[pos] = 1+longest_increasing_ending_with_element_at_pos[prev_pos]
                num_longest_increasing_ending_with_element_at_pos[pos] = num_longest_increasing_ending_with_element_at_pos[prev_pos]
            elif longest_increasing_ending_with_element_at_pos[pos] == 1+longest_increasing_ending_with_element_at_pos[prev_pos]:
                num_longest_increasing_ending_with_element_at_pos[pos] = (num_longest_increasing_ending_with_element_at_pos[pos] + num_longest_increasing_ending_with_element_at_pos[prev_pos]) % BASE

for ele,pos in zip(reversed(s[:-1]),reversed(range(n-1))):
    for next_pos in range(pos+1,n):
        if s[next_pos] < ele:
            if longest_decreasing_starting_with_element_at_pos[pos] < 1+longest_decreasing_starting_with_element_at_pos[next_pos]:
                longest_decreasing_starting_with_element_at_pos[pos] = 1+longest_decreasing_starting_with_element_at_pos[next_pos]
                num_longest_decreasing_starting_with_element_at_pos[pos] = num_longest_decreasing_starting_with_element_at_pos[next_pos]
            elif longest_decreasing_starting_with_element_at_pos[pos] == 1+longest_decreasing_starting_with_element_at_pos[next_pos]:
                num_longest_decreasing_starting_with_element_at_pos[pos] = (num_longest_decreasing_starting_with_element_at_pos[pos] + num_longest_decreasing_starting_with_element_at_pos[next_pos]) % BASE


#print(f"{longest_increasing_ending_with_element_at_pos=}")
#print(f"{longest_decreasing_starting_with_element_at_pos=}")
#print(f"{num_longest_increasing_ending_with_element_at_pos=}")
#print(f"{num_longest_decreasing_starting_with_element_at_pos=}")

max_len = 0
num_opts = 1

for apex_pos in range(n):
    if max_len < longest_increasing_ending_with_element_at_pos[apex_pos] + longest_decreasing_starting_with_element_at_pos[apex_pos] -1:
        max_len = longest_increasing_ending_with_element_at_pos[apex_pos] + longest_decreasing_starting_with_element_at_pos[apex_pos] -1
        num_opts = (num_longest_increasing_ending_with_element_at_pos[apex_pos] * num_longest_decreasing_starting_with_element_at_pos[apex_pos]) % BASE
    elif max_len == longest_increasing_ending_with_element_at_pos[apex_pos] + longest_decreasing_starting_with_element_at_pos[apex_pos] -1:
        num_opts = (num_opts + num_longest_increasing_ending_with_element_at_pos[apex_pos] * num_longest_decreasing_starting_with_element_at_pos[apex_pos]) % BASE
    

if g == 1:
    print(max_len)
else:
    assert g == 2
    print(num_opts)

