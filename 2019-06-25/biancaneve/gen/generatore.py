#!/usr/bin/env python2
from sys import argv, exit
import os, string
from numpy.random import seed, choice, shuffle, randint

usage = """Correct usage of this instance generator requires passing the following parameters.
Either:
    COPY <filename>
or:
    ZCOPY <filename>
or:
    num_nani, num_mosse, num_query, num_intervals_start, seed
"""

MAX_N = 300000 # numero nani
MAX_MOSSE = 200000 # numero mosse richieste da Biancaneve
MAX_QUERY = 200000 # numero query

if len(argv) < 2:
    print usage
    exit(1)

if argv[1] == "COPY":
    if len(argv) < 3:
        print usage
        exit(1)
    os.system("cat " + argv[2])
    exit(0)
if argv[1] == "ZCOPY":
    if len(argv) < 3:
        print usage
        exit(1)
    os.system("zcat " + argv[2])
    exit(0)

if len(argv) != 6:
    print usage
    exit(1)
    
n, num_mosse, num_query, num_intervals_start, instance_seed = map(int, argv[1:])
assert (1 <= n <= MAX_N)
assert (0 <= num_mosse <= MAX_MOSSE)
assert (0 <= num_query <= MAX_QUERY)

seed(instance_seed)

print n, num_mosse + num_query

intervals = []
for i in range(num_intervals_start-1):
    intervals.append([_ for _ in range(1+i*(n/num_intervals_start),1+(i+1)*(n/num_intervals_start))])
intervals.append([_ for _ in range(1+(num_intervals_start-1)*(n/num_intervals_start),n+1)])                 
if num_intervals_start < 2000:
    shuffle(intervals)
else:
    for i in range(num_intervals_start/800):
        shuffle(intervals[500*i:500*(i+1)])
nani = []
for i in intervals:
    if randint(2) == 0:
        nani = nani + i
    else:
        nani = nani + list(reversed(i))

for x in nani:
    print x,
print
for i in range(num_intervals_start-1):
    if num_query > 0:
        num_query -= 1
        print 2, 1+i*(n/num_intervals_start), (i+1)*(n/num_intervals_start)

while num_mosse > 0:
    num_mosse -= 1
    delta = 1+randint(n/10)
    p1 = 1+randint(n-delta -1)
    p2 = p1+1+delta
    print 1, p1, p2
    if num_query > num_mosse:
        num_query -= 1
        delta = 1+randint(n/10)
        h1 = 1+randint(n-delta -1)
        h2 = h1+1+delta
        print 2, h1, h2
                 
while num_query > 0:
    num_query -= 1
    delta = 1+randint(n/10)
    h1 = 1+randint(n-delta -1)
    h2 = h1+1+delta
    print 2, h1, h2
