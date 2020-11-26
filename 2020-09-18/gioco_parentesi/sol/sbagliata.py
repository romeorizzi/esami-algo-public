#!/usr/bin/python3
#Risale dalla foglia verso la radice per cercare la mossa vincente
import fileinput
import sys 
from collections import deque
def BUCKET(ID = -1, start = -1, end = -1, father = -1):
    a = [ID, start, end, father]
    return a

CACHE = []
ALL_BUCKETS = []

def init_globals(N):
    toReserve = int(N/2 + 1)
    global ALL_BUCKETS
    ALL_BUCKETS = [BUCKET() for _ in range(toReserve)]
    ALL_BUCKETS[0] = BUCKET(0, 0, -1, 0)
    global CACHE
    CACHE = [0 for _ in range(toReserve)]

def parser(parentesi):
    init_globals(len(parentesi))
    stack = deque()
    globalID = 0
    index = 0
    stack.appendleft(globalID)
    global ALL_BUCKETS
    global CACHE
    for c in parentesi:
        if(c == '('):
            globalID+=1
            ALL_BUCKETS[globalID] = BUCKET(globalID, index, -1, stack[0])
            stack.appendleft(globalID)
        elif(c == ')'):
            tempIndex = stack[0]
            ALL_BUCKETS[tempIndex][2] = index #end
            stack.popleft() #in pratica risalgo al padre
            ALL_BUCKETS[stack[0]][2] = index #aggiorno end del padre
            CACHE[stack[0]] ^= (CACHE[tempIndex] + 1) #aggiorno cache del padre
        else:
            exit(1)
        
        index += 1

if __name__ == "__main__":
    N = int(sys.stdin.readline())
    parentesi = sys.stdin.readline()
    parentesi = parentesi[:-1]
    assert(N == len(parentesi))

    parser(parentesi)

    risp = CACHE[0]

    if(0): #debug
        print()
        for _ in ALL_BUCKETS:
            print(_)
        print()
        print(CACHE)

    if(risp != 0):
        print(1)
        print(ALL_BUCKETS[1][1], ALL_BUCKETS[1][2])
    else:
        print(0)