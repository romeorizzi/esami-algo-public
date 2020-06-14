#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage = """Generatore di "cats".

Parametri:
* Nm (numero maschi)
* Nf (numero femmine)
* Tipo (0 normale, 1 tutti maschi uguali, 2 sequenze crescenti, 2 e 3 donne gattofile)
* S (seed)

Constraint:
* 1 <= Nm, Nf <= %d
""" % (MAXN)


def run(Nm, Nf, T):
    print(Nm, Nf)
    if T == 1:
        val = randint(0, MAXV)
        males = [val for _ in range(Nm)]  # same value for males
        females = [randint(0, MAXV) for _ in range(Nf)]
    elif T == 2 or T == 3:
        males =   [randint(0, MAXV/2) for _ in range(Nm)]
        females = [randint(MAXV/2, MAXV) for _ in range(Nf)]
        if T == 2:
            males = sorted(males)
            females = sorted(females)
    else:
        males =   [randint(0, MAXV) for _ in range(Nm)]
        females = [randint(0, MAXV) for _ in range(Nf)]

   
    # Print sequences
    for m in males:
        print(m, end=" ")
    print()
    for f in females:
        print(f, end=" ")
    print()


if __name__ == "__main__":
    if len(argv) != 5:
        print(usage)
        exit(1)

    Nm, Nf, T, S = map(int, argv[1:])

    assert (1 <= Nm <= MAXN)
    assert (1 <= Nf <= MAXN)
    assert (0 <= T <= 3)
    seed(S)
    run(Nm, Nf, T)
