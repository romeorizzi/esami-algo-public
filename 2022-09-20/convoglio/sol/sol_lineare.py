#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**9)

N, M = map(int,input().strip().split())
#print(f"{N=}, {M=}")
first_assignment = [None]*N
out_nei = [ [] for _ in range(2*N)]
for i in range(M):
    u,v = map(int,input().strip().split())
    if i < N:
        first_assignment[u] = v
        out_nei[u].append(v+N)
    else:
        out_nei[v+N].append(u)
#print(f"{first_assignment=}")
#print(f"{out_nei=}")
    
color = [None] * (2*N)

def dfs(v, dad, col):
    global color, first_assignment
    """returns the triple (found,apex_node,finished) but also act on the two global variables above.
       It returns (found,apex_node,finished) = (False,None,False) when no alternating cycle has yet been found through the whole exploration of node v. Otherwise found=True, and assuming that also finished = True, then the alternating cycle has been entirely worked out and the global variable first_assignment now contains the valid assignment obtained by applying the alternating cycle to the original assignment (i.e., the perfect matching contained in the input). Otherwise, found=True and finished=False and while an alternating cycle has been detected, the procedure is still backtracking in order to reconstruct it; in this situation, apex_node is the node where the cycle got closed and is needed internally to stop reconstructing the cycle."""
    #print(f"called dfs({v=}, {dad=}, {col=})")
    found = False
    apex_node = None
    finished = False
    color[v] = col
    for z in out_nei[v]:
        if color[z] == col and not found:
            found = True
            assert z < N  # since this is the second time I arrive to z, for sure I am now arriving to z through an edge not in the matching given in input

            first_assignment[z] = v-N
            apex_node = z
            #print(f"found: cycle closed on {apex_node=}")
            return found, apex_node, finished
        elif color[z] is None:
            found,apex_node,finished = dfs(z,v,col)
            if found:
                if apex_node == v:
                    finished = True
                if finished:
                    return found,apex_node,finished
                if v < N:
                    first_assignment[v] = dad-N
                    assert v != dad
                return found,apex_node,finished
    #print(f"{found=},{apex_node=},{finished=}")
    assert (False, None, False) == (found,apex_node,finished)
    return False, None, False

for u in range(N):
    if color[u] is None:
        found,apex_node,finished = dfs(u,u,u)
        #print(f"exploring {u=} got {found=},{apex_node=},{finished=}")
        if found:
            assert finished
            for i in range(N):
                print(f"{i} {first_assignment[i]}")
            exit(0)
print(-1)
exit(0)
