#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: sol_n_log_opt.py
 *  Soluzione di riferimento per il problema A_seq
 *  Romeo Rizzi, 2022-06-29
"""

import sys

BASE = 10**9+7
MAX_VAL = 100000

g, n = map(int,input().split()) # g in {1,2} sets the goal, n = length of the input sequence s
s = list(map(int,input().split()))
assert 1 <= g <= 2
assert 1 <= n
assert len(s) == n

# the positions of elements in s are in [0,n-1]
longest_increasing_ending_with_element_at_pos = [None] * n
longest_decreasing_starting_with_element_at_pos = [None] * n
num_longest_increasing_ending_with_element_at_pos = [None] * n
num_longest_decreasing_starting_with_element_at_pos = [None] * n

stacks = [ [] for _ in range(n+1)]  # for i in [0,n], stacks[i] contains the stack of those positions p of s such that longest_increasing_ending_with_element_at_pos[p] = i.
stacks_num_sols = [ [0] for _ in range(n+1) ]
stacks_num_sols_prefix_sums = [ [0] for _ in range(n+1) ]

s.append(MAX_VAL+1) # a dummy sentinel element of largest value
tops = [n] * (n+1) # tops[i] is meant to give the position p in s (extended with the dummy element) that is currently at the top of stacks[i]. It is used to allow binary serach. At the bottom of every stack we (virtually) place the dummy element. Initially, the tops of the stacks are these bottoms.

for ele,pos in zip(s[:-1],range(n)):
    #print(f" {tops=}, {ele=}, {pos=}")
    left = 0; right = n
    assert s[tops[right]] >= ele
    while right > left:
        middle = (left+right)//2
        if s[tops[middle]] >= ele:
            right = middle
        else:
            left = middle + 1
        assert s[tops[right]] >= ele
    longest_increasing_ending_with_element_at_pos[pos] = right + 1
    tops[right] = pos
    stacks[right].append(pos)
    if right == 0:
        num_longest_increasing_ending_with_element_at_pos[pos] = 1
    else:
        above = len(stacks[right-1]) - 1; below = 0
        assert s[stacks[right-1][above]] < ele
        while above > below:
            middle = (above+below)//2
            if s[stacks[right-1][middle]] < ele:
                above = middle
            else:
                below = middle + 1
            assert s[stacks[right-1][above]] < ele
        num_longest_increasing_ending_with_element_at_pos[pos] = stacks_num_sols_prefix_sums[right-1][-1] - stacks_num_sols_prefix_sums[right-1][below]
        num_longest_increasing_ending_with_element_at_pos[pos] %= BASE 
    stacks_num_sols[right].append(num_longest_increasing_ending_with_element_at_pos[pos])
    stacks_num_sols_prefix_sums[right].append(stacks_num_sols_prefix_sums[right][-1] + stacks_num_sols[right][-1])

# re-inizialization of the auxiliary data structure with the stacks and their tops:
stacks = [ [] for _ in range(n+1)]
stacks_num_sols = [ [0] for _ in range(n+1) ]
stacks_num_sols_prefix_sums = [ [0] for _ in range(n+1) ]
tops = [n] * (n+1)

for ele,pos in zip(reversed(s[:-1]),reversed(range(n))):
    #print(f"{tops=}, {ele=}, {pos=}, ")
    left = 0; right = n
    assert s[tops[right]] >= ele
    while right > left:
        middle = (left+right)//2
        if s[tops[middle]] >= ele:
            right = middle
        else:
            left = middle + 1
        assert s[tops[right]] >= ele
    longest_decreasing_starting_with_element_at_pos[pos] = right + 1
    tops[right] = pos
    stacks[right].append(pos)
    if right == 0:
        num_longest_decreasing_starting_with_element_at_pos[pos] = 1
    else:
        above = len(stacks[right-1]) - 1; below = 0
        assert s[stacks[right-1][above]] < ele
        while above > below:
            middle = (above+below)//2
            if s[stacks[right-1][middle]] < ele:
                above = middle
            else:
                below = middle + 1
            assert s[stacks[right-1][above]] < ele
        num_longest_decreasing_starting_with_element_at_pos[pos] = stacks_num_sols_prefix_sums[right-1][-1] - stacks_num_sols_prefix_sums[right-1][below]
        num_longest_decreasing_starting_with_element_at_pos[pos] %= BASE 
    stacks_num_sols[right].append(num_longest_decreasing_starting_with_element_at_pos[pos])
    stacks_num_sols_prefix_sums[right].append(stacks_num_sols_prefix_sums[right][-1] + stacks_num_sols[right][-1])

#print(f"{longest_increasing_ending_with_element_at_pos=}")
#print(f"{longest_decreasing_starting_with_element_at_pos=}")
#print(f"{num_longest_increasing_ending_with_element_at_pos=}")
#print(f"{num_longest_decreasing_starting_with_element_at_pos=}")

max_len = 0
num_opts = -11

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

