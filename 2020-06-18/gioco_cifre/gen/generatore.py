#!/usr/bin/env python3
from sys import argv
import random, string

if len(argv) < 2:
    exit(1)

if argv[1] != "ECHO":
    exit(1)

print(argv[2])
exit(0)


