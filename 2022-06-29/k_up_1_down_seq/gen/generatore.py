#!/usr/bin/env python3
# -*- coding: latin-1 -*-

usage="""Generatore di "k_up_1_down_seq".
 Usage syntax:
   > generatore g n k
PARAMETERS:
 * g: goal (subtask type), also the first number in the instance to be generated
 * n: the length of the sequence, also the second number in the instance to be generated
 * k: the size of the uprises
 */
"""

import random
import sys
sys.setrecursionlimit(10**6)
BASE = 10**9+7
MAX_RANK = 10**3

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

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print(usage)
        exit(1)

    g=int(sys.argv[1])
    n=int(sys.argv[2])
    k=int(sys.argv[3])
    print(f"{g} {n} {k}")
    if int(sys.argv[1]) == 2:
        print(random.randrange(min(num_sequences(n),MAX_RANK)))
    if int(sys.argv[1]) == 3:
        rank = random.randrange(min(num_sequences(n),MAX_RANK))
        print(unrank(n,rank))

