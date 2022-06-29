#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: soluzione.py
 *  Soluzione per conferma per il problema k_up_1_down_seq. Questa soluzione lenta (esponenziale)  preferisce generare innanzitutto l'intera lista ordinata delle s,k-stringa per poi rispondere a tutte le domande.
 *  Romeo Rizzi, 2022-02-02
"""

sequences = []

def num_sequences():
    return len(sequences)

def list_sequences():
    for s in sequences:
        print(s)

def unrank(r):
    return sequences[r]

def rank(s):
    for r,seq in zip(range(len(sequences)),sequences):
        if seq == s:
            return r
    assert False

def gen_sorted_list_of_sequences(num_to_be_added, history="0", last_added = 0):
    #print(f"{num_to_be_added=}, {k=}, {history=}, {last_added=}", file=sys.stderr)
    if last_added < 0 or last_added > num_to_be_added:
        return
    if num_to_be_added == 0:
        global sequences
        sequences.append(history)
        return
    gen_sorted_list_of_sequences(num_to_be_added-1, history+" "+str(last_added -1), last_added -1)
    gen_sorted_list_of_sequences(num_to_be_added-1, history+" "+str(last_added), last_added)
    gen_sorted_list_of_sequences(num_to_be_added-1, history+" "+str(last_added+k), last_added+k)

# MAIN:
g, n, k = map(int,input().split()) # g in {1,2,3,4} sets the goal, n = length of the n,k-sequence
assert 1 <= g <= 4
assert 1 <= n
assert 1 <= k

gen_sorted_list_of_sequences(n-1, history="0", last_added = 0)

if g == 1:
    print(num_sequences())
elif g == 2:
    r = int(input())
    print(unrank(r))
elif g == 3:
    s = input()
    print(rank(s))
else:
    assert g == 4
    list_sequences()

