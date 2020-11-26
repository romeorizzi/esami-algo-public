#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <queue>

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

vector<BUCKET> ALL_BUCKETS;
vector<size_t> CACHE;

void init(size_t len) {
    size_t toReserve = len/2 + 1;
    CACHE = vector<size_t>(toReserve, 0);
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
            stack.push_front(globalID);
        } else if (c == ')') {
            size_t tempIndex = stack.front();
            ALL_BUCKETS[tempIndex].end = index;
            stack.pop_front();
            ALL_BUCKETS[stack.front()].end = index;
            CACHE[stack.front()] ^= (CACHE[tempIndex] + 1);
        } else {
            exit(1);
        }
        index++;
    }
}

int main() {
    size_t len;
    cin >> len;
    string parentesi;
    cin >> parentesi;
    assert(len == parentesi.size());

    parser(parentesi);
    auto risp = CACHE[0];
#ifndef EVAL
    cout << ALL_BUCKETS << endl;
    cout << "RISP: " << risp  << endl << "DFS:" << endl;
    for(size_t i = 0; i < CACHE.size(); i++) {
        cout << "I: " << i << " --> " << CACHE[i] << endl;
    }
#endif
    cout << (bool)risp << endl;
    if(risp) {
        for(size_t i = 1; i < ALL_BUCKETS.size(); i++) {
            size_t j = i;
            size_t tryOne = CACHE[ALL_BUCKETS[j].father] ^ (CACHE[j] + 1);
            j = ALL_BUCKETS[j].father;
            while(j) {
                tryOne = (tryOne + 1) ^ CACHE[ALL_BUCKETS[j].father] ^ (CACHE[j] + 1);
                j = ALL_BUCKETS[j].father;
            }

            if(!tryOne) {
                cout << ALL_BUCKETS[i].start << " " << ALL_BUCKETS[i].end << endl;
                return 0;
            }
        }
    }

    return 0;
}