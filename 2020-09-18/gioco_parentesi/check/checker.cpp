// Assume file di input non malformati.

#include <iostream>
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <limits>
#include <queue>

using namespace std;

ifstream fin;  // File di input
ifstream fcor; // File di output
ifstream fout; // File da correggere

using BUCKET = struct
{
    size_t ID;
    size_t start;
    size_t end;
    size_t father;
};
vector<BUCKET> ALL_BUCKETS;
vector<size_t> CACHE;
vector<size_t> INDEX_TO_BUCKET;

void init(size_t len)
{
    size_t toReserve = len / 2 + 1;
    CACHE = vector<size_t>(toReserve, 0);
    ALL_BUCKETS = vector<BUCKET>(toReserve);
    INDEX_TO_BUCKET = vector<size_t>(len);
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
            ALL_BUCKETS[++globalID] = BUCKET({globalID, index, ~0u, stack.front()});
            stack.push_front(globalID);
            INDEX_TO_BUCKET[index] = globalID;
        }
        else if (c == ')')
        {
            size_t tempIndex = stack.front();
            INDEX_TO_BUCKET[index] = tempIndex;
            ALL_BUCKETS[tempIndex].end = index;
            stack.pop_front();
            ALL_BUCKETS[stack.front()].end = index;
            CACHE[stack.front()] ^= (CACHE[tempIndex] + 1);
        }
        else
        {
            exit(1);
        }
        index++;
    }
}

void ex(const char *msg, float res)
{
    if (msg)
    {
        cerr << msg;
    }
    cout << res << endl;
    exit(0);
}

template <class T>
T safe_read(istream &source, const T &lower = numeric_limits<T>::min(), const T &upper = numeric_limits<T>::max())
{
    // Legge un valore da source, assicurandosi che sia tra lower e upper
    if (lower > upper)
    {
        cerr << "safe_read chiamato con parametri errati: " << lower << " " << upper << "\n";
        exit(1);
    }

    T x;
    source >> x;
    if (source.fail() /*|| source.eof ()*/) //eof non e' un errore!!!!!
    {
        ex("Output malformato.", 0.0f);
    }
    if (x < lower || x > upper)
    {
        ex("Output invalido.", 0.0f);
    }
    return x;
}

void check_fine_file()
{
    string x;
    fout >> x;
    if (!fout.eof())
    {
        ex("Output malformato.", 0.0f);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cerr << "Usage: " << argv[0] << " <input> <correct output> <test output>" << endl;
        return 1;
    }

    fin.open(argv[1]);
    fcor.open(argv[2]);
    fout.open(argv[3]);

    if (fin.fail())
    {
        cerr << "Impossibile aprire il file di input " << argv[1] << "." << endl;
        return 1;
    }
    if (fcor.fail())
    {
        cerr << "Impossibile aprire il file di output corretto " << argv[2] << "." << endl;
        return 1;
    }
    if (fout.fail())
    {
        ex("Impossibile aprire il file di output generato dal codice sottoposto al problema.", 0.0);
    }

    size_t len;
    fin >> len;
    string parentesi;
    fin >> parentesi;

    assert(len == parentesi.size());

    parser(parentesi);

    auto risp = CACHE[0];

    auto output_risp = safe_read<size_t>(fout);
    if (bool(risp) != output_risp)
    {
        ex("Output invalido.", 0.0f);
    }
    if (risp)
    {
        size_t y1, y2;
        y1 = safe_read<size_t>(fout);
        y2 = safe_read<size_t>(fout);
        if (y1 > len - 1 || y2 > len - 1 || y1 >= y2 || INDEX_TO_BUCKET[y1] != INDEX_TO_BUCKET[y2])
        {
            ex("Output malformato. Controlla gli intervalli.", 0.0f);
        }
        size_t j = INDEX_TO_BUCKET[y1];
        size_t tryOne = CACHE[ALL_BUCKETS[j].father] ^ (CACHE[j] + 1);
        j = ALL_BUCKETS[j].father;
        while(j) {
            tryOne = (tryOne + 1) ^ CACHE[ALL_BUCKETS[j].father] ^ (CACHE[j] + 1);
            j = ALL_BUCKETS[j].father;
        }
        if (tryOne)
        {
            ex("Output invalido.", 0.0f);
        }
    }

    check_fine_file();

    ex("Corretto.", 1.0f);

    return 0;
}
