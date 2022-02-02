#!/usr/bin/env python3

"""FILE: generatore.py  problem: block_diag_mat  last change: 2022-02-02  author: Romeo Rizzi
 Randomly generates an mxn matrix of naturals that can be decomposed in a diagonal block matrix of at least b blocks according to task type t that decides which decompositions are possible (t=1 only square principal blocks, t=2 principal blocks can be rectangular matices, t=3 like t=2 but one can also independently permute the rows and the colums of the matrix).
"""

usage="""Generatore di "bridges_and_cutnode".
 Usage syntax:
   > generatore t m n b seed
PARAMETERS:
 * t: subtask type, also the first number in the instance to be generated
 * m: number of rows of the integer matrix to be generated as an instance to the problem
 * n: number of columns of the integer matrix
 * b: maximum number of blocks in the semantic set up by the subtask parameter t (t=1 only square principal blocks, t=2 principal blocks can be rectangular matices, t=3 like t=2 but one can also independently permute the rows and the colums of the matrix). NOTE HOWEVER: this parameter offers only a lower-bound, but it is quite likely to be tight.
 * seed: seed for the pseudo-random generation
 */
"""

import sys
import random
from limiti import *

def run(t, m, n, b):
    print (t, m, n)
    M = [ [0] * n for _ in range(m) ]
    last_rows = sorted(random.sample(range(m-1), b-1)) +[m-1]
    last_cols = sorted(random.sample(range(n-1), b-1)) +[n-1]
    if t==1:
        assert m == n
        last_cols = last_rows
    first_r = 0
    first_c = 0
    for last_r, last_c in zip(last_rows,last_cols):
        for i in range(first_r,last_r+1):
            for j in range(first_c,last_c+1):
              M[i][j] = random.randrange(10)
        first_r = last_r+1
        first_c = last_c+1
    new_label_col=list(range(n)) # to begin with, the identity (no shuffling of the columns)
    if t == 3:
        random.shuffle(M)       
        random.shuffle(new_label_col)
    for row in M:
        print(" ".join(map(str,[row[new_label_col[j]] for j in range(n)])))

if __name__ == "__main__":
    if len(sys.argv) != 6:
        print(usage)
        exit(1)

    t,m,n,b,seed = map(int, sys.argv[1:])

    assert t in {1,2,3}
    assert 1 <= m <= MAXM
    assert 1 <= n <= MAXN
    assert 0 <= b <= min(m,n)
    random.seed(seed)
    run(t,m,n,b)
