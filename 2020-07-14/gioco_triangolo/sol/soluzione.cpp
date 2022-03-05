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
            cout << "T" << " " << x << " " << y1 << " " << y2 << endl;
	    //ossia: se l'avversario (primo a giocare), gioca sul tavolo Nim (quindi y2=0 ) e rimpiazza un numero x con un numero x' < x  allora io (secondo a giocare) gioco sul tavolo Triangolo dove (dato che rispondiamo ad una singola mossa) posso assumere sia presente x, e lo sostituisco col valore y1)
	    // Ho così ripristinato che le liste dei tue tavoli abbiano lo stesso Nim value (di fatto le liste sui due tavoli sono la stessa) e posso applicare induzione. 
        } else { //faccio una mossa equivalente sull'altro tavolo
            cout << "N" << " " << x << " " << 0 << " " << (y1 ^ y2) << endl;
	    //ossia: se l'avversario (primo a giocare), gioca sul tavolo Triangolo e rimpiazza un numero x con due numeri y1 e y2 (con y1 + y2) < x allora io (secondo a giocare) gioco sul tavolo Nim dove (dato che rispondiamo ad una singola mossa) posso assumere sia presente x, e lo sostituisco col valore bitwiseXOR(y1,y2)
	    // Ho così ripristinato che le liste dei tue tavoli abbiano lo stesso Nim value e posso applicare induzione (anche se le liste sui due tavoli non sono la stessa, nell'eventuale proseguio del gioco vale comunque l'invariante che le liste dei tue tavoli hanno lo stesso Nim value).

	    // per gestire l'intera partita, dobbiamo poggiare sull'ipotesi induttiva che i Nim value delle due liste siano lo stesso, e osservare che:
	    // se due liste L1 e L2 hanno lo stesso Nim value, allora, comunque uno abbia Nim mosso (x2=0) o Triangle mosso x -> x1, x2 (con x1+x2<x) comportando che il Nim value sia passato da 0 a bitwiseXOR(x,x1,x2), deve essere tuttavia presente o in L1 o in L2 un altro valore y >= max_power_o_2_in(x) e quindi ci basterà abbassare y a bitwiseXOR(x,x1,x2) per riportare il Nim value a zero. (Il face-value di y può anche essere lo stesso di x, volevamo solo essere chiari sul fatto che è un altro elemento). 
        }

    } else { //Solo Triangolo.
        cout << (bool) risposta << endl;
        if(risposta) {
            //cerco un elemento della lista adatto per portare triangolo in una situa safe
            uint32_t rollback;
            for(auto i : lista) {
                rollback = risposta ^ i;
                if(rollback < i) {
                    cout << "T" << " " << i << " " << 0 << " " << rollback << endl;
                    return 0;
                }
            }
            assert(1 == 0);
        }
    }
    return 0;
}
