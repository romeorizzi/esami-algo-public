#!/usr/bin/env python3
import fileinput

fin = fileinput.input()
goal, n, m = map(int,fin[0].split())
#print(f"goal={goal}, n={n}, m={m}")
nei = [-1] + [ [] for v in range(n) ]
for i in range(m):
    u,v = map(int,fin[1+i].split())
    #print(f"u={u}, v={v}")
    if u < v:
        nei[u].append(v)
    else:
        nei[v].append(u)
        
if goal==1 or goal==2:
    nei2 = [-1] + [ [] for v in range(n) ]
    for u in range(1,n+1):
        for v in nei[u]:
            nei2[v].append(u)
        
if goal==1:        
    j = None        
    for jj in range(3,n+1):
        pos_jj = 0
        pos_jjprev = 0
        while pos_jj < len(nei2[jj]) and nei2[jj][pos_jj] < jj-1:
            if pos_jjprev >= len(nei2[jj-1]):
                j = jj
                break
            jjprev_nei = nei2[jj-1][pos_jjprev]
            pos_jjprev += 1
            if jjprev_nei > nei2[jj][pos_jj]:
                j = jj
                break
            elif jjprev_nei == nei2[jj][pos_jj]:
                pos_jj += 1
            else:
                break
        if j != None:
            break
    if j == None:
        print(1)
        exit(0)
    else:
        print(0)
        for ii in range(1,j):
            pos_jj = 0
            pos_ii = 0
            while pos_jj < len(nei2[jj]) and nei2[jj][pos_jj] < ii:
                if pos_ii >= len(nei2[ii]):
                    print(j,ii,nei2[jj][pos_jj])
                    exit(0)
                ii_nei = nei2[ii][pos_ii]
                pos_ii += 1
                if ii_nei > nei2[jj][pos_jj]:
                    print(j,ii,nei2[jj][pos_jj])
                    exit(0)
                elif ii_nei == nei2[jj][pos_jj]:
                    pos_jj += 1
                else:
                    break
        assert(False)
elif goal==2:
    for i in range(2,n+1):
        j = nei2[i][-1]
        pos_i = 0
        pos_j = 0
        while pos_i < len(nei2[i])-1:
            if pos_j >= len(nei2[j]):
                print(i)
                exit(0)
            j_nei = nei2[j][pos_j]
            i_nei = nei2[i][pos_i]
            pos_j += 1
            if j_nei > i_nei:
                print(i)
                exit(0)
            elif j_nei == i_nei:
                pos_i += 1
    for i in reversed(range(1,n+1)):
        print(i, end=" ")
    print()
    exit(0)
else:
    c = [None] *(n+1)
    taken = [False] *(n+1)    
    i_max_clique = n
    c[n] = 1
    for i in reversed(range(1,n+1)):
        if len(nei[i_max_clique]) < len(nei[i]):
            i_max_clique = i
            c[i] = 1+len(nei[i])
        else:
            for v in nei[i]:
                taken[c[v]] = True
            c[i] = 1
            while taken[c[i]]:
                c[i] += 1
            for v in nei[i]:
                taken[c[v]] = False
    print(1+len(nei[i_max_clique]))
    # BEGIN: only checks
    for u in range(1,n+1):
        for v in nei[u]:
            assert(c[v] != c[u])
    for u in nei[i_max_clique]:
        for v in nei[i_max_clique]:
            if u < v:
                assert(v in nei[u])
    # END: only checks
    if goal==3:
        exit(0)
    elif goal==4:
        print(i_max_clique,end=" ")
        for v in sorted(nei[i_max_clique]):
            print(v,end=" ")
        print()
        exit(0)
    elif goal==5:
        for i in range(1,n+1):
            print(c[i],end=" ")
        print()
        exit(0)
    else:
        assert(False)
