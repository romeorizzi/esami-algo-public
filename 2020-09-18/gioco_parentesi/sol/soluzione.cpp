#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <queue>
#include <sys/resource.h>

using BUCKET = struct {
                        size_t ID;
                        size_t start;
                        size_t end;
                        size_t father;
                      };

// PRETTY PRINT RUBATO - PER DEBUG PARSER
#include <algorithm>
#include <iterator>
#ifndef EVAL
std::ostream & operator<<(std::ostream & os, BUCKET bucket)
{
    os<<"[ ";
    os<< bucket.ID << "<" << bucket.father << ">:(" << bucket.start << "," << bucket.end << ")";
    os<<" ]";
    return os;
}

std::ostream & operator<<(std::ostream & os, BUCKET* bucket_ptr)
{
    if(bucket_ptr) {
        os<< *bucket_ptr;
    }
    return os;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec)
{
    os<<"{ ";
    for(auto it = vec.begin(); it != vec.end(); it++) os << *it << " ";
    os<<"}";
    return os;
}
#endif
//

using namespace std;

vector<vector<BUCKET*>> TREE_BUCKETS;
vector<BUCKET> ALL_BUCKETS;
vector<size_t> CACHE;

size_t DFS(size_t index, size_t ignore = ~0u) {
    if(CACHE[index] != ~0u) return CACHE[index];
    assert(index != ignore);
    size_t risposta = 0;
    for(size_t i = 0; i < TREE_BUCKETS[index].size(); i++){
        if(TREE_BUCKETS[index][i]->ID != ignore) {
            risposta ^= (DFS(TREE_BUCKETS[index][i]->ID, ignore) + 1);
        }
    }
    return CACHE[index] = risposta; 
}


void init(size_t len) {
    size_t toReserve = len/2 + 1;
    TREE_BUCKETS.reserve(toReserve);
    for(size_t i = 0; i < toReserve; i++) {
        TREE_BUCKETS.push_back(vector<BUCKET*>());
    }
    CACHE = vector<size_t>(toReserve, ~0u);
    ALL_BUCKETS = vector<BUCKET>(toReserve);
}

void parser(string& s) {
    size_t globalID = 0;
    deque<size_t> stack;
    stack.push_front(0);
    init(s.size());
    size_t index = 0;
    for(auto c: s){
        if(c == '(') {
            globalID += 1;
            ALL_BUCKETS[globalID] = BUCKET({globalID,index,~0u,stack.front()});
            assert(ALL_BUCKETS[globalID].ID == globalID);
            TREE_BUCKETS[stack.front()].push_back(&ALL_BUCKETS[globalID]);
            stack.push_front(globalID);
        } else if (c == ')') {
            ALL_BUCKETS[stack.front()].end = index;
            stack.pop_front();
            ALL_BUCKETS[stack.front()].end = index;
        } else {
            exit(1);
        }
        index++;
    }
}

void resetCache(size_t index) {
    while(index != 0){
        CACHE[index] = ~0u;
        index = ALL_BUCKETS[index].father;
    }
    CACHE[0] = ~0u;
}

int main() {
    const rlim_t kStackSize = 64 * 1024 * 1024;
    struct rlimit rl;
    int result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                exit(1);
            }
        }
    }
    size_t len;
    cin >> len;
    string parentesi;
    cin >> parentesi;
    assert(len == parentesi.size());

    parser(parentesi);
    auto risp = DFS(0);
#ifndef EVAL
    cout << TREE_BUCKETS << endl << endl << endl;
    cout << ALL_BUCKETS << endl;
    cout << "RISP: " << risp  << endl << "DFS:" << endl;
    for(size_t i = 0; i < CACHE.size(); i++) {
        cout << "I: " << i << " --> " << CACHE[i] << endl;
    }
#endif
    cout << (bool)risp << endl;
    if(risp) {
        for(size_t i = 1; i < ALL_BUCKETS.size(); i++) {
            resetCache(i);
            resetCache(i - 1);
            auto tryOne = DFS(0, i);
            if(!tryOne) {
                cout << ALL_BUCKETS[i].start << " " << ALL_BUCKETS[i].end << endl;
                return 0;
            }
        }
    }

    return 0;
}