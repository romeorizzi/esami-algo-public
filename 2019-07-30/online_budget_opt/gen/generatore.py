#!/usr/bin/env python2

import limiti
from varie import *
from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

usage="""Generatore di "online_budget". (@Romero Rizzi 2019).
Descrizione: Nella prima riga scrive N e poi B0.
Nella seconda riga genera una sequenza pseudocasuale di N interi tutti compresi tra LowerBoundOnVals e UpperBoundOnVals.

Parametri:
* t (type)
* N (numero)
* B0 (numero)
* LowerBoundOnVals (numero)
* UpperBoundOnVals (numero)
* S (seed)

Constraints:
* t = 1,2
* 1 <= N <= %d
* 0 <= B0
* %d <= LowerBoundOnVals <= UpperBoundOnVals <= %d
""" % (limiti.MAXN,limiti.MINVAL,limiti.MAXVAL)


def run(t, N, B0, LowerBoundOnVals, UpperBoundOnVals):
    print N, B0, t
    print " ".join(map(str, [randint(LowerBoundOnVals, UpperBoundOnVals +1) for i in xrange(0, N)]))
    q = list(range(1001))
    shuffle(q)
    q = list(q)
    for i in xrange(0,N):    
        print q[i%1000],
    print

if __name__ == "__main__":
    if len(argv) != 7:
        print usage
        exit(1)

    t, N, B0, LowerBoundOnVals, UpperBoundOnVals, S = map(int, argv[1:])
    assert (1 <= t <= 2)
    assert (1 <= N <= limiti.MAXN)
    assert (0 <= B0)
    assert(limiti.MINVAL <= LowerBoundOnVals)
    assert(LowerBoundOnVals <= UpperBoundOnVals)
    assert(UpperBoundOnVals <= limiti.MAXVAL)

    # su seed non positivo copia un input di esempio dal .tex
    if S <= 0:
        print extract_input()[-S],
        exit(0)
    nseed(S)
    rseed(S)
    run(t, N, B0, LowerBoundOnVals, UpperBoundOnVals)

