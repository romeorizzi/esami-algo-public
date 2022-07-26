#!/usr/bin/env python3
import sys

MOD=1000000007

g,N,K = list(map(int,input().strip().split()))
panino = list(map(int,input().strip().split()))
P= [ [0] * N for k in range(K+1) ]  #  P[i][k] = massima lunghezza di una sottosequenza crescente con ESATTAMENTE k crolli che inizi prendendo l'elemento i-esimo come suo primo elemento.
num_opts= [ [None] * N for k in range(K+1) ] #  num_opts[i][k] = numero di soluzioni ottime al probema P[i][k]. Ossia numero di sottosequenza crescente con al più k crolli di massima lunghezza tra quelle che iniziano prendendo l'elemento i-esimo come loro primo elemento.
opt_val=0
num_global_opts=1 # vi è una solo sottoinsieme vuoto dell'insieme degli indici i in range(N)
for i in range(N-1,-1,-1):
  P[0][i] = 1    # soluzione: prendere solo quel panino
  num_opts[0][i] = 1 # vi è un solo modo di prendere solo quel panino
  for k in range(K+1):
      for j in range(i+1,N):   
        if panino[j]>panino[i]: # il panino j candida per essere il secondo panino
            if 1+P[k][j] > max(k,P[k][i]):
                P[k][i] = 1+P[k][j]
                num_opts[k][i] = num_opts[k][j]
                #print(f"reset j={j},[k,i]=[{k},{i}],num_opts[k][i]={num_opts[k][i]}")
            elif 1+P[k][j] == P[k][i] > k:
                num_opts[k][i] =  (num_opts[k][i] + num_opts[k][j]) % MOD
                #print(f"added j={j},[k,i]=[{k},{i}],num_opts[k][i]={num_opts[k][i]}")
        elif k>0:
            if 1+P[k-1][j] > max(k,P[k][i]):
                P[k][i] = 1+P[k-1][j]
                num_opts[k][i] = num_opts[k-1][j]
                #print(f"reset j={j},[k,i]=[{k},{i}],num_opts[k][i]={num_opts[k][i]}")
            elif 1+P[k-1][j] == P[k][i]  > k:
                num_opts[k][i] = (num_opts[k][i] + num_opts[k-1][j]) % MOD
                #print(f"added j={j},[k,i]=[{k},{i}],num_opts[k][i]={num_opts[k][i]}")
      if P[k][i] > opt_val:
          opt_val = P[k][i]
          num_global_opts = num_opts[k][i]
      elif P[k][i] == opt_val:
          num_global_opts = (num_global_opts + num_opts[k][i]) % MOD

#print(f"input    ={panino}")
#for k in range(K+1):
#  print(f"P[{k}]       ={P[k]}")
#for k in range(K+1):
#  print(f"num_opts[{k}]={num_opts[k]}")
          
if g==1:
    print(opt_val)
else:    
    print(num_global_opts)
exit(0)
