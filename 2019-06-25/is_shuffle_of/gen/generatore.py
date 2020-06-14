#!/usr/bin/env python2

import sys
from numpy.random import seed, choice, shuffle, randint


MAX_VAL = 10
MAX_M = 1000
MAX_N = 1000
m, n, max_val, x_all_zero, w_is_shuffle_for_sure, output_type, instance_seed = map(int, sys.argv[1:])
assert (1 <= m <= MAX_M)
assert (1 <= n <= MAX_N)
assert (0 <= max_val <= MAX_VAL)
assert (0 <= x_all_zero <= 1)
assert (0 <= w_is_shuffle_for_sure <= 1)
assert (0 <= output_type <= 1)

seed(instance_seed)

print m, n, output_type

# make x
if x_all_zero == 1:
    x = [0]*m
else:
    x = choice(max_val+1, m, replace=True)

# make x
y = choice(max_val+1, n, replace=True)

# make w
i = 0
j = 0
w = []
while len(w) < m+n:
    assert i+j == len(w)
    take = randint(2)
    if i >= m:
        take = 1
    if j >= n:
        take = 0
    if take == 0:
        w.append(x[i])
        i += 1
    if take == 1:
        w.append(y[j])
        j += 1
if not w_is_shuffle_for_sure:
    shuffle(w[(m+n)/4:(3*(m+n))/4])

# printing
for val in x:
    print val,
print
for val in y:
    print val,
print
for val in w:
    print val,
print
