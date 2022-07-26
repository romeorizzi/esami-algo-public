#!/usr/bin/env python3
import sys

g,N,K = list(map(int,input().strip().split()))
panino = list(map(int,input().strip().split()))
P= [ [1] * N +[0] for k in range(K+1) ]  #  P[i][k] = massima lunghezza di una sottosequenza crescente con al più k crolli che inizi prendendo l'elemento i-esimo come suo primo elemento.

best_val=0     
for i in range(N-1,-1,-1):
  for k in range(K+1):
      for j in range(i+1,N):   
        if panino[j]>panino[i]: # il panino j candida per essere il secondo panino
            P[k][i] = max(P[k][i], 1+P[k][j])
        elif k>0:
            P[k][i] = max(P[k][i], 1+P[k-1][j])
      if P[k][i] > best_val:
          best_val = P[k][i]
print(best_val)

exit(0)
