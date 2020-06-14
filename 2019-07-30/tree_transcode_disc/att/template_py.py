#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
sys.setrecursionlimit(100000)
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3

"""Template per soluzione in python per il problema tree_transcode_disc
Romeo Rizzi, per l'appello di algoritmi 2019-07-28
"""

MAX_N = 1000000

seq = list(map(int,input().split()))

# in questo template di soluzione mi limito a ricopiare l'input in output (non sarà mai la soluzione corretta tranne che per alberi di un solo nodo):
for val in seq:
    print(val,end=" ")
    
print()
