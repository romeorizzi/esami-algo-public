#include<iostream>
#include<cassert>
#include<vector>
using namespace std;
int main() {
    uint32_t t, N;
    cin >> t >> N;
    assert(t == 1 || t == 2);

    if(t == 1) {  //Doppio gioco
        if(N == 2) { //PRIMO ESEMPIO
            cout << "T 2 0 0";
        } else { //TERZO ESEMPIO
            cout << "T 2 1 0";
        }
    } else {
        if(N == 2) { //SECONDO ESEMPIO
            cout << "1 T 2 1 0";
        } else { //QUARTO ESEMPIO
            cout << "0";
        }
    }
    return 0;
}