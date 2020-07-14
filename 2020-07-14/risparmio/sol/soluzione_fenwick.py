#!/usr/bin/env python3
A = [0] * 100000
F = [0] * 100000

def upd(x, val):
    x += 1

    while x <= N:
        F[x - 1] += val
        x += x & -x


def get(x):
    x += 1
    sol = 0
    while x:
        sol += F[x - 1]
        x -= x & -x
    return sol


N, M = [int(x) for x in input().split(' ')]

for i in range(M):
    op = [int(x) for x in input().split(' ')]
    t = op[0]

    if t == 1:
        x = op[1]
        A[x] ^= 1
        # If it's on
        if A[x]:
            # and the previous is off, a new range starts here
            if not x or not A[x - 1]:
                upd(x, 1)

            # If the next one is on, it's no longer the start of a light range
            if x < N - 1 and A[x + 1]:
                upd(x + 1, -1)
        # If it's off, we have multiple cases:
        elif not A[x]:

            # If the previous is off, this light was the start of a range, and now it's not.
            if not x or not A[x - 1]:
                upd(x, -1)

            # If the next light is on, it's the start of a new range
            if x < N - 1 and A[x + 1]:
                upd(x + 1, 1)

    elif t == 2:
        x = op[1]
        y = op[2]
        intlast = get(y)
        intfirst = get(x - 1) if x != 0 else 0

        # printf("FIRST: [%d]%d LAST: [%d]%d\n", x, intfirst, y+1, intlast)
        offbyone = A[x] and (x and A[x - 1])
        totint = intlast - intfirst + (1 if offbyone else 0)
        print(totint)