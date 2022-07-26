#!/usr/bin/env python3

"""FILE: generatore.py  problem: incr_subseq_with_drops  last change: 2021-07-29  author: Romeo Rizzi
"""

usage="""Generatore di "incr_subseq_with_drops".
 Usage syntax:
   > generatore g N k maxVal seed
PARAMETERS:
 - g è il goal/tipo di richiesta
 - N è la lunghezza della sequenza in input
 - k il numero di croli concessi
 -  tutti i numeri nella sequenza in input saranno ricompresi nell'intervallo [1,maxVAL]
 - seed è il seme per la pseudo-random generation
"""

import sys
import random
from limiti import *

MAXN = 200


def run(g, N, k, maxVal, seed):
    print(f"{g} {N} {k}")
    for i in range(N):
      print(random.randint(1, maxVal), end=" ")
    print()

if __name__ == "__main__":
    if len(sys.argv) != 6:
        print(usage)
        exit(1)

    g, N, k, maxVal, seed = map(int, sys.argv[1:])
    assert 1 <= g <= 2
    assert 1 <= N <= MAXN
    assert 0 <= k <= MAXN
    assert 1 <= maxVal
    random.seed(seed)
    run(g, N, k, maxVal, seed)
