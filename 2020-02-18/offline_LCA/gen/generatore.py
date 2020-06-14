#!/usr/bin/env python2

# generates a random forest as for problem offline-LCA (esame Algoritmi 2020-02-18, Romeo Rizzi)

import sys
import random
sys.setrecursionlimit(10000000)

MAXN = 1000000
N, Q, only_same_tree_queries, only_w_equals_v, num_trees, max_deg, seed = map(int, sys.argv[1:])

random.seed(seed)
nodes = range(N)
random.shuffle(nodes)
p = [-1]*N

def lay_subtree(root, left, right):
    global nodes
    #print root, left, right
    if right-left < max_deg:
        for v in nodes[left:right]:
            p[v] = root
    else:
        num_children = random.randint(1, max_deg)
        new_left = left+num_children
        size = min(1,(right-left - num_children)/num_children) 
        for v in nodes[left:new_left]:
            p[v] = root
            lay_subtree(v, new_left, new_left+size)
            new_left = new_left+size

left = num_trees
size = (N - num_trees)/num_trees 
for v in nodes[:num_trees]:
    lay_subtree(v, left,left+size)
    left = left+size
    
print N, Q
for val in p:
    print val,
print
for i in range(Q):
    u = random.randint(0, N-1)
    if only_same_tree_queries == 1:
        w = -1
    else:
        w = random.randint(0, N-1)
    if only_w_equals_v == 1:
        v = w
    else:
        v = random.randint(0, N-1)
        def path2root(v):
            path = [v]
            while p[v] != -1:
                v = p[v]
                path.append(v)
            return path
        def f(q):
            if q > 100000:
                return 5000
            if q > 1000:
                return 100
            if q > 500:
                return 15
            if q > 100:
                return 10
            return 4
            
        if w != -1:
            if random.randint(0, f(Q)) == 2:
                path_u = path2root(u)    
                path_v = path2root(v)
                if path_u[-1] == path_v[-1]:
                    w = path_u[-1]
                    finished = len(path_u) == 0 or len(path_v) == 0
                    while not finished:
                        nu = path_u.pop()
                        nv = path_v.pop()
                        if nu == nv:
                            w = nu
                            finished = len(path_u) == 0 or len(path_v) == 0
                        else:
                            finished = True    
            
    print u, v, w
