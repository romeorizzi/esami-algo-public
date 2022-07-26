#!/usr/bin/env python3
import sys
import itertools

g,N,K = list(map(int,input().strip().split()))
colesterolo = list(map(int,input().strip().split()))

def check_subseq(char_vector):
  num_drops = 0
  val=0
  colesterolo_last_taken = None
  for i in range(len(char_vector)):
      if char_vector[i] == 1:
          if colesterolo_last_taken != None:
              if colesterolo[i] <= colesterolo_last_taken:
                num_drops += 1
                if num_drops > K:
                  return None
          colesterolo_last_taken = colesterolo[i]
          val += 1
  return val

opt_val=0
num_global_opts=1
for char_vector in itertools.product([0, 1], repeat=N):
    answ=check_subseq(char_vector)
    if answ != None:
        if answ > opt_val:
            opt_val = answ
            num_global_opts = 1
        elif answ == opt_val:
            num_global_opts += 1

# Now a second run:

num_global_opts=0
for char_vector in itertools.product([0, 1], repeat=N):
    answ=check_subseq(char_vector)
    if answ != None:
        if answ > opt_val:
            opt_val = answ
            num_global_opts = 1
        elif answ == opt_val:
            num_global_opts += 1
            for i in range(len(char_vector)):
                if char_vector[i] == 1:
                  print(colesterolo[i], end=" ")
            print()

            
if g==1:
    print(opt_val)
else:    
    print(num_global_opts)
exit(0)
