#!/usr/bin/env python3
# -*- coding: latin-1 -*-

# Soluzione di two_three_step 2023-02-20

with open("input.txt", "r") as fr:
    n = int(fr.readline())
    val = list(map(int,fr.readline().split()))

dyn = [0,0,0]
for i in reversed(range(n)):
    dyn[i%3] = val[i] + max(dyn[(i+2)%3], dyn[i%3])

with open("output.txt", "w") as fw:
    fw.write(str(dyn[0]) + "\n")

    
