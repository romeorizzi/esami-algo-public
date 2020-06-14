# template di soluzione per il problema biancaneve

# template di soluzione che, pur con sintassi di python3, possa girare anche entro environment pensati per supportare python2

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, l'equivalente di input è raw_input

n, m = map(int,input().split())

print("NO\nYES")
