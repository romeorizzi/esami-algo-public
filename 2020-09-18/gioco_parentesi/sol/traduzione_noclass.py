#!/usr/bin/python3
#traduzione della soluzione in cpp, senza uso di classi per evitare un dizionario. ~10% piu' veloce
import fileinput
import sys 
sys.setrecursionlimit(10**5) 
from collections import deque
def BUCKET(ID = -1, start = -1, end = -1, father = -1):
    a = [ID, start, end, father]
    return a

CACHE = []
ALL_BUCKETS = []
TREE_BUCKETS = []
def DFS(index, ignore = -1):
    global CACHE
    if(CACHE[index] != -1):
        return CACHE[index]
    risposta = 0
    for i in TREE_BUCKETS[index]:
        if(ALL_BUCKETS[i][0] != ignore):
            risposta = risposta ^ (DFS(i, ignore) + 1)
    CACHE[index] = risposta
    return risposta


def init_globals(N):
    toReserve = int(N/2 + 1)
    global TREE_BUCKETS
    TREE_BUCKETS = [[] for _ in range (toReserve)]
    global ALL_BUCKETS
    ALL_BUCKETS = [BUCKET() for _ in range(toReserve)]
    ALL_BUCKETS[0] = BUCKET(0, 0, -1, 0)
    global CACHE
    CACHE = [-1 for _ in range(toReserve)]

def parser(parentesi):
    init_globals(len(parentesi))
    stack = deque()
    globalID = 0
    index = 0
    stack.appendleft(globalID)
    global ALL_BUCKETS
    global TREE_BUCKETS
    global CACHE
    for c in parentesi:
        if(c == '('):
            globalID+=1
            ALL_BUCKETS[globalID] = BUCKET(globalID, index, -1, stack[0])
            TREE_BUCKETS[stack[0]].append(globalID)
            stack.appendleft(globalID)
        elif(c == ')'):
            ALL_BUCKETS[stack[0]][2] = index
            stack.popleft()
            ALL_BUCKETS[stack[0]][2] = index
        else:
            exit(1)
        
        index += 1


def resetCache(index):
    global CACHE
    while(index != 0):
        CACHE[index] = -1
        index = ALL_BUCKETS[index][3]
    CACHE[0] = -1

if __name__ == "__main__":
    N = int(sys.stdin.readline())
    parentesi = sys.stdin.readline()
    parentesi = parentesi[:-1]
    assert(N == len(parentesi))

    parser(parentesi)

    risp = DFS(0)

    if(0): #debug
        print(TREE_BUCKETS)
        print()
        for _ in ALL_BUCKETS:
            print(_)
        print()
        print(CACHE)

    if(risp != 0):
        print(1)
        for i in range(1, len(TREE_BUCKETS)):
            resetCache(i)
            resetCache(i - 1)
            tryOne = DFS(0, i)
            if(tryOne == 0):
                print(ALL_BUCKETS[i][1],ALL_BUCKETS[i][2])
                break
    else:
        print(0)