#!/usr/bin/python3
#traduzione della soluzione in cpp
import fileinput
import sys 
sys.setrecursionlimit(10**5) 
from collections import deque
class BUCKET():
    ID: int = -1
    start: int = -1
    end: int = -1
    father: int = -1
    def __init__(self, **kv):
        self.__dict__.update(kv)

CACHE = []
ALL_BUCKETS = []
TREE_BUCKETS = []
def DFS(index, ignore = -1):
    global CACHE
    if(CACHE[index] != -1):
        return CACHE[index]
    risposta = 0
    for i in TREE_BUCKETS[index]:
        if(ALL_BUCKETS[i].ID != ignore):
            risposta = risposta ^ (DFS(i, ignore) + 1)
    CACHE[index] = risposta
    return risposta


def init_globals(N):
    toReserve = int(N/2 + 1)
    global TREE_BUCKETS
    TREE_BUCKETS = [[] for _ in range (toReserve)]
    global ALL_BUCKETS
    ALL_BUCKETS = [BUCKET() for _ in range(toReserve)]
    ALL_BUCKETS[0] = BUCKET(ID = 0, start = 0, end = -1, father = 0)
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
            ALL_BUCKETS[globalID] = BUCKET(ID = globalID, start = index, end = -1, father = stack[0])
            TREE_BUCKETS[stack[0]].append(globalID)
            stack.appendleft(globalID)
        elif(c == ')'):
            ALL_BUCKETS[stack[0]].end = index
            stack.popleft()
            ALL_BUCKETS[stack[0]].end = index
        else:
            exit(1)
        
        index += 1


def resetCache(index):
    global CACHE
    while(index != 0):
        CACHE[index] = -1
        index = ALL_BUCKETS[index].father
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
            print(_.ID, _.start, _.end, _.father)
        print()
        print(CACHE)

    if(risp != 0):
        print(1)
        for i in range(1, len(TREE_BUCKETS)):
            resetCache(i)
            resetCache(i - 1)
            tryOne = DFS(0, i)
            if(tryOne == 0):
                print(ALL_BUCKETS[i].start,ALL_BUCKETS[i].end)
                break
    else:
        print(0)