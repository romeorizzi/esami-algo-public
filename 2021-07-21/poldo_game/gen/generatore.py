#!/usr/bin/env python3

"""FILE: generatore.py  problem: poldo_game  last change: 2021-07-29  author: Romeo Rizzi
"""

usage="""Generatore di "bridges_and_cutnode".
 Usage syntax:
   > generatore N min_colesterolo_poldo max_colesterolo_poldo min_colesterolo_dottore max_colesterolo_dottore seed
PARAMETERS:
 * N: numero di panini (portate)
 * min_colesterolo_poldo, max_colesterolo_poldo: il valore di colesterolo per i panini la cui scelta spetta a poldo è nell'intervallo [min_colesterolo_poldo,max_colesterolo_poldo]
 * min_colesterolo_dottore, max_colesterolo_dottore: il valore di colesterolo per i panini la cui scelta spetta al dottore è nell'intervallo [min_colesterolo_dottore,max_colesterolo_dottore]
 * seed: seed for the pseudo-random generation
 */
"""

import sys
import random
from limiti import *

MAXN = 200


def run(N, min_colesterolo_poldo, max_colesterolo_poldo, min_colesterolo_dottore, max_colesterolo_dottore):
    print(N)
    for i in range(N):
      if i%2==0:
          print(random.randint(min_colesterolo_poldo,max_colesterolo_poldo), end=" ")
      else:
          print(random.randint(min_colesterolo_dottore, max_colesterolo_dottore), end=" ")
    print()

if __name__ == "__main__":
    if len(sys.argv) != 7:
        print(usage)
        exit(1)

    N, min_colesterolo_poldo, max_colesterolo_poldo, min_colesterolo_dottore, max_colesterolo_dottore, seed = map(int, sys.argv[1:])
    assert (1 <= N <= MAXN)
    assert (0 <= min_colesterolo_poldo <= max_colesterolo_poldo)
    assert (0 <= min_colesterolo_dottore <= max_colesterolo_dottore)
    random.seed(seed)
    run(N, min_colesterolo_poldo, max_colesterolo_poldo, min_colesterolo_dottore, max_colesterolo_dottore)
