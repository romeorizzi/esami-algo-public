#!/usr/bin/env python3
# -*- coding: latin-1 -*-

with open("input.txt", "r") as fr:
    n = int(fr.readline())
    val = list(map(int,fr.readline().split()))
    assert len(val) == n


# TO DO !

with open("output.txt", "w") as fw:
    fw.write(str(42) + "\n")

    
