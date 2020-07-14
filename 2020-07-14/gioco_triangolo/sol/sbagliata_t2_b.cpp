#include<iostream>
#include<cassert>
#include<vector>
using namespace std;
int main() {
    uint32_t t, N;
    cin >> t >> N;
    assert(t == 1 || t == 2);
    uint32_t risposta = 0u;
    uint32_t temp;
    //uint32_t old = 0;
    vector<uint32_t> lista;
    lista.reserve(N);
    for(uint32_t i = 0; i < N; i++) {
        cin >> temp;
        risposta ^= temp;
        lista.push_back(temp);
        /*
        if(i > 0) { //e' o non e' un triangolo?!?
            assert(temp >= old);
        }
        
        old = temp;
        */
    }
    if(t == 1) {  //Doppio gioco
      
        char tavolo;
        cin >> tavolo;
        assert(tavolo == 'T' || tavolo == 'N');
        uint32_t x, y1, y2;
        cin >> x >> y1 >> y2;
        assert(x > 0 && (y1 + y2) < x);
        if(tavolo == 'N') { // copio la mossa sull'altro tavolo
            cout << "T" << endl << x << endl << y1 << endl << y2;
        } else { //faccio una mossa equivalente sull'altro tavolo
            cout << "N" << endl << x << endl << 0 << endl << (y1 ^ y2);
        }

    } else { //Solo Triangolo.
        cout << (bool) risposta << endl;
        if(risposta) {
            //cerco un elemento della lista adatto per portare triangolo in una situa safe
            uint32_t rollback;
            for(auto i : lista) {
                rollback = risposta ^ i;
                if(rollback < i) {
                    cout << "T" << endl << i << endl << 0 << endl << rollback + 1;
                    return 0;
                }
            }
            assert(1 == 0);
        }
    }
    cout << endl;
    return 0;
}