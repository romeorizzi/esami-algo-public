#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
sys.setrecursionlimit(100000)
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione di tree_transcode_disc
   Autore: Romeo Rizzi
   Descrizione: 
"""

MAX_N = 1000000

seq = list(map(int,input().split()))

def pre2post(pos):
    massa_dichiarata = seq[pos]
    massa_raccolta = 1
    while massa_raccolta < massa_dichiarata:
        massa_raccolta += pre2post(pos + massa_raccolta)
    assert massa_raccolta == massa_dichiarata
    print(massa_dichiarata,end=" ")
    return massa_raccolta

if seq[0] == 1:
    print(2,end=" ")
    pre2post(1)
else:
    assert seq[0] == 2
    print(1,end=" ")
    father_of = [None]*len(seq)
    stack = []
    # now, with a linear scan and using the stack, for every pos, we write in father_of[pos] the position of the father of the node in position pos 
    for pos in range(1, len(seq)):
        gathered_mass = 1
        while gathered_mass < seq[pos]:
            child_pos = stack.pop()
            father_of[child_pos] = pos
            gathered_mass += seq[child_pos]
        assert gathered_mass == seq[pos]
        stack.append(pos)

    #print(father_of)
    printed = [False]*len(seq)
            
    def print_down_path_to(pos):
        if father_of[pos] != None and not printed[father_of[pos]]:
            print_down_path_to(father_of[pos])
        print(seq[pos],end=" ")
        printed[pos] = True

    for pos in range(1, len(seq)):
        if seq[pos] == 1:
            print_down_path_to(pos)

print()
