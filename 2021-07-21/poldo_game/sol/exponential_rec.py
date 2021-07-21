#!/usr/bin/env python3
import sys

N=int(input().strip())
colesterolo = list(map(int,input().strip().split())) # I panini (portate) sono numerati partendo da 0. Sugli indici pari sceglie Poldo cui spetta scegliere ad esempio sulla prima portata.
colesterolo.append(0)   #viene comodo un (N+1)-esimo panino fittizio con questo valore di colesterolo.

def opt_val(i, j):
    """numero di portate che verrebbero infine assaggiate se fossero interdette tutte le portate con valore di colesterolo <= colesterolo[j] e tutte le portate che precedono l'i-esima.
# Note: I panini (portate) sono numerati partendo da 0. Il primo a scegliere resta determinato da i%2 secondo la regola che sugli indici pari sceglie Poldo, cui ad esempio spetta di scegliere sulla prima portata."""
    if i>=N:
        return 0
    if colesterolo[i] <= colesterolo[j]:
        return opt_val(i+1, j)
    P_i_se_non_mangio_i = opt_val(i+1, j)
    P_i_se_mangio_i = 1 + opt_val(i+1, i)
    if i%2==0:  #sceglie poldo
        return max(P_i_se_mangio_i, P_i_se_non_mangio_i)
    if i%2==1:  #sceglie il dottore
        return min(P_i_se_mangio_i, P_i_se_non_mangio_i)

print(opt_val(0, N))
        
exit(0)
