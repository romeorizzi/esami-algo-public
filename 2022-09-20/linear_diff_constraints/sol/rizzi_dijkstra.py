#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from grader import get_inputs, print_answer_and_exit
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
    #print("H={H}, sum(H)={sum(H)}")
answer = sum(H)
# end solution

print_answer_and_exit(answer)
