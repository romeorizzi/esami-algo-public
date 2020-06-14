# -*- coding: utf-8 -*-
# template di soluzione per il problema is_shuffle_of

# template di soluzione che, pur con sintassi di python3, possa girare anche entro environment pensati per supportare python2

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, l'equivalente di input è raw_input

fin = open("input.txt", "r")
m, n, with_cert = map(int,fin.readline().split())

fout = open("output.txt", "w")
fout.write("0")

fin.close()
fout.close() 
