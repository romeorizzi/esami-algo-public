#!/usr/bin/env python3
import sys

DEBUG = 0
#DEBUG = 1

N=int(input().strip())
colesterolo = list(map(int,input().strip().split())) # I panini (portate) sono numerati partendo da 0. Sugli indici pari sceglie Poldo cui spetta scegliere ad esempio sulla prima portata.
colesterolo.append(0)   #viene comodo un (N+1)-esimo panino fittizio con questo valore di colesterolo. 
P= [ [0] * (N+1) for j in range(N+1) ]  #  P[j][i] = numero di portate che verrebbero infine assaggiate se fossero interdette tutte le portate con valore di colesterolo <= colesterolo[j] e tutte le portate che precedono l'i-esima.
# Note: I panini (portate) sono numerati partendo da 0. Il primo a scegliere resta determinato da i%2 secondo la regola che sugli indici pari sceglie Poldo, cui ad esempio spetta di scegliere sulla prima portata.

for i in range(N-1,-1,-1):
    for j in range(N+1):
        P_i_se_non_mangio_i = P[j][i+1]
        if colesterolo[i] <= colesterolo[j]:
            P[j][i] = P_i_se_non_mangio_i
        else:
            P_i_se_mangio_i = 1 + P[i][i+1]
            if i%2==0:  #sceglie poldo
                P[j][i] = max(P_i_se_mangio_i, P_i_se_non_mangio_i)
            if i%2==1:  #sceglie il dottore
                P[j][i] = min(P_i_se_mangio_i, P_i_se_non_mangio_i)
print(P[N][0])
        
if DEBUG:
    for i in range(N):
        print(f"{P[N][i]}", end=" ")
    print("\n")
exit(0)
