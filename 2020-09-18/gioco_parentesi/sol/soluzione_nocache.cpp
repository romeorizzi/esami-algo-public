#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <queue>
#include <sys/resource.h>

using BUCKET = struct
{
    size_t ID;
    size_t start;
    size_t end;
    size_t father;
};

using namespace std;

vector<vector<BUCKET *>> TREE_BUCKETS;
vector<BUCKET> ALL_BUCKETS;

size_t DFS(size_t index, size_t ignore = ~0u)
{
    assert(index != ignore);
    size_t risposta = 0;
    for (size_t i = 0; i < TREE_BUCKETS[index].size(); i++)
    {
        if (TREE_BUCKETS[index][i]->ID != ignore)
        {
            risposta ^= (DFS(TREE_BUCKETS[index][i]->ID, ignore) + 1);
        }
    }
    return risposta;
}

void init(size_t len)
{
    size_t toReserve = len / 2 + 1;
    TREE_BUCKETS.reserve(toReserve);
    for (size_t i = 0; i < toReserve; i++)
    {
        TREE_BUCKETS.push_back(vector<BUCKET *>());
    }
    ALL_BUCKETS = vector<BUCKET>(toReserve);
}

void parser(string &s)
{
    size_t globalID = 0;
    deque<size_t> stack;
    stack.push_front(0);
    init(s.size());
    size_t index = 0;
    for (auto c : s)
    {
        if (c == '(')
        {
            globalID += 1;
            ALL_BUCKETS[globalID] = BUCKET({globalID, index, ~0u, stack.front()});
            assert(ALL_BUCKETS[globalID].ID == globalID);
            TREE_BUCKETS[stack.front()].push_back(&ALL_BUCKETS[globalID]);
            stack.push_front(globalID);
        }
        else if (c == ')')
        {
            ALL_BUCKETS[stack.front()].end = index;
            stack.pop_front();
            ALL_BUCKETS[stack.front()].end = index;
        }
        else
        {
            exit(1);
        }
        index++;
    }
}

int main()
{
    size_t len;
    cin >> len;
    string parentesi;
    cin >> parentesi;
    assert(len == parentesi.size());

    parser(parentesi);
    auto risp = DFS(0);

    cout << (bool)risp << endl;
    if (risp)
    {
        for (size_t i = 1; i < ALL_BUCKETS.size(); i++)
        {
            auto tryOne = DFS(0, i);
            if (!tryOne)
            {
                cout << ALL_BUCKETS[i].start << " " << ALL_BUCKETS[i].end << endl;
                return 0;
            }
        }
    }
    return 0;
}