#!/usr/bin/env python3
# -*- coding: latin-1 -*-

from __future__ import print_function
import sys
if sys.version_info < (3, 0):
    input = raw_input # in python2, raw_input svolge la funzione della primitiva input in python3
    

"""Soluzione di pacman_opt 
   Autore: Romeo Rizzi, 2020-02-13
   Descrizione: alfa-beta-tree ricorsivo con memoizzazione. Algoritmo esponenziale sia in tempo che in memoria.
"""
from copy import deepcopy

DEBUG1 = False
DEBUG2 = False
DEBUG3 = False

MAXM = 100
MAXN = 100

M, N, ghosts_move, wall_cost, T = map(int,input().split())
assert 1 <= M <= MAXM
assert 1 <= N <= MAXN

conf0 = [ ['#'] * (N+2)]
for line in sys.stdin:
    conf0.append(['#'])
    conf0[-1] += [ x for x in line.rstrip('\n\r') ]
    conf0[-1] += ['#']
conf0.append( ['#'] * (N+2))

assert len(conf0) == M+2
if DEBUG1:
    print(conf0, file=sys.stderr)

settled_conf_p_2move = {}
settled_conf_g_2move = {}
    
def ric_p_2move(conf,gems_count,char_below_g1,char_below_g2,ip,jp,i1,j1,i2,j2,t):
    """returns -1 if, starting from configuration conf, the pacman can not get to the exit in time (given it has already done t moves), otherwise it returns the number of gems it can secure with itself.
    Here gems_count, char_below_g1 and char_below_g2 are actaully part of the current configuration/state of the game.
    More precisely:
       gems_count = the current gems balance for the pacman, that is, collected - used
       char_below_g1 = the char with the number of gems in the cell where ghost 1 is currently placed
       char_below_g2 = the char with the number of gems in the cell where ghost 2 is currently placed 
    Though the configuration is fully specified with (conf,gems_count,char_below_g1,char_below_g2), still it is convenient to make directly accessible the coordinates of the actors in the grid rather than having to searcm them within the conf matrix.
    One could also grasp the general sense of this signature by looking at the main body of the program more below."""
    if DEBUG2:
        print(f"ric_p_2move called with t={t},gems_count={gems_count},char_below_g1={char_below_g1},char_below_g2={char_below_g2},ip={ip},jp={jp},i1={i1},j1={j1},i2={i2},j2={j2},conf={conf}", file=sys.stderr)
    assert(conf[ip][jp] == 'P')
    assert(conf[i1][j1] == 'G')
    assert(conf[i2][j2] == 'G')
    if t >= T:
        return -1
    if (''.join([''.join(row) for row in conf]),gems_count,char_below_g1,char_below_g2,t) in settled_conf_p_2move:
        return settled_conf_p_2move[(''.join([''.join(row) for row in conf]),gems_count,char_below_g1,char_below_g2,t)]
    risp = -1
    for ip_diff in [-1,0,1]:
       for jp_diff in [-1,0,1]:
           if ip_diff * jp_diff == 0 and ip_diff + jp_diff != 0 and conf[ip + ip_diff][jp + jp_diff] not in {'#','G'}:
               i_new = ip + ip_diff
               j_new = jp + jp_diff
               if conf[i_new][j_new] == 'E':
                   risp = max(risp,gems_count)
               else:
                   new_conf = deepcopy(conf)
                   new_gems_count = gems_count
                   new_conf[ip][jp] = '0'
                   new_gems_count += ord(new_conf[i_new][j_new]) - ord('0')
                   new_conf[i_new][j_new] = 'P'
                   if DEBUG3:
                       print(f"Pacman move (no wall made): ip_diff={ip_diff},jp_diff={jp_diff}")
                   if ghosts_move == 1:
                       risp = max(risp,ric_g_2move(new_conf,new_gems_count,char_below_g1,char_below_g2,i_new,j_new,i1,j1,i2,j2,t+1))
                   else:
                       risp = max(risp,ric_p_2move(new_conf,new_gems_count,char_below_g1,char_below_g2,i_new,j_new,i1,j1,i2,j2,t+1))                       
                   if gems_count >= wall_cost and ghosts_move == 1:
                      new_gems_count -= wall_cost                       
                      new_conf[ip][jp] = '#'
                      if DEBUG3:
                          print(f"Pacman move (wall made): ip_diff={ip_diff},jp_diff={jp_diff}")
                      risp = max(risp,ric_g_2move(new_conf,new_gems_count,char_below_g1,char_below_g2,i_new,j_new,i1,j1,i2,j2,t+1))
    
    settled_conf_p_2move[(''.join([''.join(row) for row in conf]),gems_count,char_below_g1,char_below_g2,t)] = risp
    return risp

def ric_g_2move(conf,gems_count,char_below_g1,char_below_g2,ip,jp,i1,j1,i2,j2,t):
    """returns -1 if, starting from configuration conf (where the pacman has already moved, and the turn is now to the ghosts), the pacman can not get to the exit in time (given it has already done t moves), otherwise it returns the number of gems the pacman can secure with itself to the exit.
    The signature is the same as for procedure ric_pmove (see what said there) and one could also get its general sense by looking at the main body of the program more below."""
    if DEBUG2:
        print(f"ric_g_2move called with t={t},gems_count={gems_count},char_below_g1={char_below_g1},char_below_g2={char_below_g2},ip={ip},jp={jp},i1={i1},j1={j1},i2={i2},j2={j2},conf={conf}", file=sys.stderr)
    assert(conf[ip][jp] == 'P')
    assert(conf[i1][j1] == 'G')
    assert(conf[i2][j2] == 'G')
    if (''.join([''.join(row) for row in conf]),gems_count,char_below_g1,char_below_g2,t) in settled_conf_g_2move:
        return settled_conf_g_2move[(''.join([''.join(row) for row in conf]),gems_count,char_below_g1,char_below_g2,t)]
    risp = 10*M*N
    for i1_diff in [-1,0,1]:
       for j1_diff in [-1,0,1]:
           if i1_diff * j1_diff == 0 and i1_diff + j1_diff != 0 and conf[i1 + i1_diff][j1 + j1_diff] != '#':
               i1_new = i1 + i1_diff
               j1_new = j1 + j1_diff
               if conf[i1_new][j1_new] == 'P':
                   settled_conf_g_2move[(''.join([''.join(row) for row in conf]),gems_count,char_below_g1,char_below_g2,t)] = -1
                   return -1
               for i2_diff in [-1,0,1]:
                   for j2_diff in [-1,0,1]:
                       if i2_diff * j2_diff == 0 and i2_diff + j2_diff != 0 and conf[i2 + i2_diff][j2 + j2_diff] != '#':
                           i2_new = i2 + i2_diff
                           j2_new = j2 + j2_diff
                           if conf[i2_new][j2_new] == 'P':
                               settled_conf_g_2move[(''.join([''.join(row) for row in conf]),gems_count,char_below_g1,char_below_g2,t)] = -1
                               return -1
                           else:
                               new_conf = deepcopy(conf)
                               new_conf[i1][j1] = char_below_g1
                               new_conf[i2][j2] = char_below_g2
                               new_char_below_g1 = new_conf[i1_new][j1_new]
                               new_char_below_g2 = new_conf[i2_new][j2_new]
                               new_conf[i1_new][j1_new] = 'G'
                               new_conf[i2_new][j2_new] = 'G'
                               if DEBUG3:
                                  print(f"Ghosts move: i1_diff={i1_diff},j1_diff={j1_diff},i2_diff={i2_diff},j2_diff={j2_diff}")
                               risp = min(risp,ric_p_2move(new_conf,gems_count,new_char_below_g1,new_char_below_g2,ip,jp,i1_new,j1_new,i2_new,j2_new,t))
    
    settled_conf_g_2move[(''.join([''.join(row) for row in conf]),gems_count,char_below_g1,char_below_g2,t)] = risp
    return risp

# MAIN BODY OF THE PROGRAM:

ip = jp = i1 = j1 = i2 = j2 = None
for i in range(M+2):
   for j in range(N+2):
       if conf0[i][j] == 'P':
           ip = i
           jp = j
       if conf0[i][j] == 'G':
           if i1 == None:
              i1 = i
              j1 = j
           else:
              i2 = i
              j2 = j
del i, j
           
print(ric_p_2move(tuple(conf0),0,'0','0',ip,jp,i1,j1,i2,j2,0))

