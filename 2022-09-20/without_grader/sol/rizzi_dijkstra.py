#!/usr/bin/env python3
# -*- coding: latin-1 -*-

def get_inputs():
    n, m = map(int,input().strip().split())
    h = list(map(int,input().strip().split()))
    a = []
    b = []
    c = []
    for _ in range(m):
        A,B,C = map(int,input().strip().split())
        a.append(A)
        b.append(B)
        c.append(C)
    return n,m,h,a,b,c

def print_answer_and_exit(answer):
    print(answer)
    exit(0)

N,M,H,A,B,C = get_inputs()

# begin solution
from queue import PriorityQueue
q = PriorityQueue()
for i,h in enumerate(H):
    q.put((h,i))
bounds_set_by = [ [] for _ in range(N)]
for a,b,c in zip(A,B,C):
    bounds_set_by[a].append((b,c))
while not q.empty():
    h_a,a = q.get()
    for b,c in bounds_set_by[a]:
        if H[b] > h_a + c:
            H[b] = h_a + c
            q.put((H[b],b))
    #print(f"H={H}, sum(H)={sum(H)}")
answer = sum(H)
# end solution

print_answer_and_exit(answer)
