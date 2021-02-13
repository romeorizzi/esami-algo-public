#!/usr/bin/env python3

from limiti import *

usage="""Generatore per "turni (esteso)".
WARNING: se C > 0 genera solo input "risolubili", ossia in cui e` possibile coprire tutti i giorni.

Parametri:
* T in {0,1}  0 se il solver deve tornare il numero di giorni scoperti, 1 se il solver deve tornare il minimo numero di persone coinvolte. 
* K (numero di giorni)
* N (numero di intervalli)
* C (se C > 0 la soluzione sara` <= C, altrimenti non sarà possibile coprire tutti i giorni)
* S (seed)

Constraint:
* 0 <= T <= 1
* 2 <= K <= %d
* 2 <= N <= %d
* C <= N
""" % (MAXK, MAXN)

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

def change(x, lim, f, p=20):
    while x != lim and randint(100) >= p:
        x = f(x)
    return x

def squeeze_interval(a, b): # genera un intervallo contenuto in [a,b]
    assert a <= b, f"called squeeze_interval(a={a}, b={b})"
    a = change(a, b, lambda x: x + 1, p=30) # left squeeze
    b = change(b, a, lambda x: x - 1, p=30) # right squeeze
    return [a, b]

def rand_triang(n):
    sum_of_two_dices = 2*n
    while sum_of_two_dices > n-1:
        sum_of_two_dices = randint(n)+randint(n)
    return sum_of_two_dices

def genera_cover(left, right_plus, card):
    span = right_plus - left
    right_endpoints = sorted([left + rand_triang(span) for _ in range(card-1)]) + [right_plus-1]
    left_endpoints = [left]
    for i in range(1, card):
        left_endpoints.append(randint(left, 1+right_endpoints[i-1]) )
    interval_cover = [ [a,b] for a,b in zip(left_endpoints, right_endpoints) ]
    #print(f"interval_cover={interval_cover}")
    return interval_cover

def covering_family(left, right_plus, card, upper_bound_min_cover):
    c_fam = genera_cover(left, right_plus, upper_bound_min_cover)
    #print(f"c_fam={c_fam}")
    for i in range(card-upper_bound_min_cover):
        j = randint(len(c_fam))
        width = c_fam[j][1]-c_fam[j][0] +1
        a = min((left+2*c_fam[j][0])//3,max(left,c_fam[j][0]-width//3))
        b = max(min(right_plus-1, c_fam[j][1]+width//3), c_fam[j][1]+min((right_plus-c_fam[j][1])//3,width//3))
        new_interval = squeeze_interval(a,b)
        c_fam.append(new_interval)
    return c_fam

def run(T, K, N, C, S):
    nseed(S); rseed(S)
    print(T)
    print(K)
    print(N)
    if C > 0:
        l = covering_family(0,K,N,C)
    else:
        l =  covering_family(0, K//2-randint(K//5), N//2, max(1,N//4))
        l += covering_family(K//2+randint(K//5),K,(N+1)//2,max(1,N//4))
    shuffle(l)
    assert len(l) == N
    for x, y in l:
        assert 0 <= x <= y < K
        print(x, y)

if __name__ == "__main__":
    if len(argv) != 6:
        print(usage)
        exit(1)

    T, K, N, C, S = [int(x) for x in argv[1:]]
    assert(0 <= T <= 1)
    assert(2 <= K <= MAXK)
    assert(2 <= N <= MAXN)
    assert(C <= N)
    run(T, K, N, C, S)
