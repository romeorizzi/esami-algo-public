/*
Generatore di input per il problema gioco_parentesi.

arg1 --> N, lunghezza della stringa da generare
arg2 --> seed
[arg3] --> k > 0, forza la stampa di k gruppi in forma (^n)^n
[arg3] --> Se uguale a 0, forza una configurazione perdente.
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

#define MAX_LEN 1000000
#define OFFSET 1
#define LOG2(X) ((unsigned)(8 * sizeof(unsigned long long) - __builtin_clzll((X)) - 1))

namespace std
{
    uint64_t uniqueIDCounter = OFFSET;
    class NODO
    {
    public:
        NODO(uint64_t id) : uniqueID(id){};
        NODO()
        {
            uniqueID = uniqueIDCounter;
            uniqueIDCounter += OFFSET;
        };
        vector<NODO> figli;
        uint64_t uniqueID; //per debug.
    };
} // namespace std

using namespace std;

/*
Divide il nodo in bucket in base alla sua lunghezza. Ogni bucket sara' un figlio e rappresentera' una "parentesi".
Ogni bucket viene ridiviso ricorsivamente.
I colori gia' usati hanno una maggior possibilita' di essere usati di nuovo per aumentare il grado di difficolta'.
*/
void recursiveCall(NODO &node, int len)
{
#ifdef DEBUGME
    cout << "LEN:" << len << " ID:" << node.uniqueID << endl;
#endif
    assert(!(len % 2));
    if (len == 2)
    {
        return;
    }
    else
    {
        //sottraggo 2, ovvero le "parentesi esterne"
        len -= 2;
        int logC = LOG2(len + 1) + 1;

        //Bucket troppo grandi semplificano troppo la vita.
        //Per esempio con lunghezza mille la dimensione massima viene fissata a 500, cosi' da avere ALMENO due bucket.
        int maxBucketSize = max(1, len / ((rand() % logC) + 1));
        int bucketSize;

        //Continuo a suddividere finche' ho ancora spazio a disposizione.
        while (len > 0)
        {
            bucketSize = min(len, 1 + (rand() % maxBucketSize));
            bucketSize += bucketSize % 2;

            //Aggiungo un nuovo figlio
            node.figli.push_back(NODO());

            //Suddivido anche il figlio
            recursiveCall(*node.figli.rbegin(), bucketSize);
            len -= bucketSize;

#ifdef DEBUGME
            if (node.uniqueID == OFFSET)
                cout << "LEN:" << len << " ID:" << node.uniqueID << " B:" << bucketSize << " M:" << maxBucketSize << endl;
#endif
        }
    }
}

/*
Solo il primo nodo verra' ignorato.
Vedi --> treeMode
*/
void visitPrint(NODO &node, bool ignoreMe = false)
{
    if (!ignoreMe)
    {
        cout << "(";
    }
    for (size_t i = 0; i < node.figli.size(); i++)
    {
        visitPrint(node.figli[i]);
    }
    if (!ignoreMe)
    {
        cout << ")";
    }
}

/*
Generazione formula con parentesi.
Dopo una serie di chiamate ricorsive in cui si genera un albero, alla fine con una visita si ottiene una cosa molto simile ad una formula formata da parentesi.
La prima parentesi e' "invisibile", cosi' da ottenere una formula che non e' necessariamente fatta cosi':
((.........)(.......).....(......))
ma molto piu' probabilmente sara':
(.........)(.......).....(......)

Se il secondo parametro è true, genera una configurazione perdente generando una configurazione lunga len/2 e poi ripetendola.
*/
void treeMode(int &len, bool forceLose = false)
{
    NODO radice = NODO(0);

    if (forceLose)
    {
        assert(len > 2);
        len /= 2;
    }
    recursiveCall(radice, len + 2);

    visitPrint(radice, true);
    if (forceLose)
    {
        visitPrint(radice, true);
    }
}

void powMode(int len, int k)
{
    int expected = min(len, 2 * (len / k));
    while (--k)
    {
        int groupSize = min(max(2, rand() % (len - (2 * k))), 2 + rand() % expected);
        groupSize += groupSize % 2;
        for (int i = 0; i < groupSize / 2; i++)
        {
            cout << "(";
        }
        for (int i = 0; i < groupSize / 2; i++)
        {
            cout << ")";
        }
        len -= groupSize;
    }
    for (int i = 0; i < len / 2; i++)
    {
        cout << "(";
    }
    for (int i = 0; i < len / 2; i++)
    {
        cout << ")";
    }
}

int main(int argc, char **argv)
{
    assert(argc > 2);

    int len = atoi(argv[1]);
    assert(len <= MAX_LEN && len > 0 && !(len % 2));

    int seed = atoi(argv[2]);
    srand(seed);

    //Prima riga: lunghezza della sequenza
    cout << len << endl;

    //Seconda ed ultima riga: la sequenza
    if (argc > 3)
    {
        int k = atoi(argv[3]);
        assert(k >= 0 && k <= len / 2);
        if (k > 0)
        {
            //Forza una configurazione (^n)^n
            powMode(len, k);
        }
        else
        {
            //Forza una configurazione perdente.
            treeMode(len, true);
        }
    }
    else
    {
        treeMode(len);
    }
    cout << endl;

    return 0;
}
