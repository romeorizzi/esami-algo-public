#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
sys.setrecursionlimit(100000)
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Soluzione di tree_split_out
   Autore: Romeo Rizzi
"""

MAX_N = 1000000

seq = list(map(int,input().split()))

def make_evaporated1(pos,level):
    num_children = seq[pos]
    num_grand_children = 0
    gathered_descendants = 1
    seq_evaporated = []
    called_children = 0
    while called_children < num_children:
        child_descendants, child_num_children, child_seq_evaporated = make_evaporated1(pos + gathered_descendants,level+1) 
        called_children += 1
        gathered_descendants += child_descendants
        num_grand_children += child_num_children
        seq_evaporated += child_seq_evaporated
    if level%2 == 0:
        seq_evaporated = [num_grand_children] + seq_evaporated
    return gathered_descendants, num_children, seq_evaporated

def make_evaporated2(pos,level):
    original_mass = seq[pos]
    seq_evaporated = []
    gathered_new_mass = 0
    if level%2 == 0:
        gathered_new_mass = 1
    gathered_old_mass = 1
    while gathered_old_mass < original_mass:
        child_old_mass, child_new_mass, child_seq_evaporated = make_evaporated2(pos + gathered_old_mass,level+1) 
        gathered_old_mass += child_old_mass
        gathered_new_mass += child_new_mass
        seq_evaporated += child_seq_evaporated
    assert gathered_old_mass == original_mass
    if level%2 == 0:
        seq_evaporated = [gathered_new_mass] + seq_evaporated
    return gathered_old_mass, gathered_new_mass, seq_evaporated

if seq[0] == 1:
    print(1,end=" ")
    num_descendants_of_root, num_children_of_root, seq_evaporated = make_evaporated1(1,0)
    assert num_children_of_root == seq[1]
    for level in seq_evaporated:
        print(level,end=" ")
if seq[0] == 2:
    print(2,end=" ")
    gathered_old_mass, gathered_new_mass, seq_evaporated = make_evaporated2(1,0)
    assert gathered_old_mass == seq[1]
    for level in seq_evaporated:
        print(level,end=" ")
if seq[0] == 3:
    print(3,end=" ")
    for level in seq[1:]:
        if level %2 == 0:
            print(level//2,end=" ")
print()
