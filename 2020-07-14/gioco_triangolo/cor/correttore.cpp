/*
  Luca Wehrstedt
 */

// Assume file di input e file di output non malformati.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <limits>
#include <unordered_map>

using namespace std;

ifstream fin; // File di input
ifstream fcor; // File di output
ifstream fout; // File da correggere

void ex (const char *msg, float res)
{
	if (msg)
	{
		cerr << msg;
	}
	cout << res << endl;
	exit (0);
}

template <class T>
T safe_read (istream& source, const T& lower = numeric_limits<T>::min (), const T& upper = numeric_limits<T>::max ())
{
	// Legge un valore da source, assicurandosi che sia tra lower e upper
	if (lower > upper)
	{
		cerr << "safe_read chiamato con parametri errati: " << lower << " " << upper << "\n";
		exit (1);
	}

	T x;
	source >> x;
	if (source.fail () /*|| source.eof ()*/) //eof non e' un errore!!!!!
	{
		ex ("Output malformato", 0.0f);
	}
	if (x < lower || x > upper)
	{
		ex ("Output invalido", 0.0f);
	}
	return x;
}

void check_fine_file ()
{
	string x;
	fout >> x;
	if (!fout.eof ())
	{
		ex ("Output malformato.", 0.0f);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		cerr << "Usage: " << argv[0] << " <input> <correct output> <test output>" << endl;
		return 1;
	}

	fin.open (argv[1]);
	fcor.open (argv[2]);
	fout.open (argv[3]);

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
		ex ("Impossibile aprire il file di output generato dal codice sottoposto al problema.", 0.0);
	}

    uint32_t t, N;
    fin >> t >> N;
    uint32_t risposta = 0u;
    uint32_t temp;
    unordered_map<uint32_t,uint32_t> N_Set;
    for(uint32_t i = 0; i < N; i++) {
        fin >> temp;
        if(N_Set.find(temp) == N_Set.end()) {
            N_Set[temp] = 1;
        } else {
            N_Set[temp] += 1;
        }
        risposta ^= temp;
    }
    char input_table;
    do {
        fin >> input_table;
    } while(input_table != 'T' && input_table != 'N');
    uint32_t input_x, input_y1,input_y2;
    fin >> input_x >> input_y1 >> input_y2;

    if(t == 2) {
        //1. Controllo del Risultato
        uint32_t output_result = safe_read<uint32_t> (fout);
        if(output_result != 1 && output_result != 0) {
            ex ("Output invalido. Vincitore invalido.", 0.0f);
        }
        if ((bool)risposta != output_result) {
            ex ("Output invalido.", 0.0f);
        }
        if(output_result) {
        
            //2. Controllo del tavolo scelto
            char output_table;
            do {
                output_table = safe_read<char> (fout);
            } while(output_table != 'T' && output_table != 'N');
            if(output_table != 'T') {
                ex ("Output invalido. Tavolo dovrebbe essere T", 0.0f);
            }

            //3. Controllo della mossa
            uint32_t output_x, output_y1, output_y2;
            output_x = safe_read<uint32_t> (fout);
            if(N_Set.find(output_x) == N_Set.end()) {
                ex ("Output invalido. Il valore X non era nella lista originale", 0.0f);
            }
            output_y1 = safe_read<uint32_t> (fout);
            output_y2 = safe_read<uint32_t> (fout);
            if(output_y1 + output_y2 >= output_x) {
                ex ("Output invalido. La somma degli yi deve essere inferiore ad X", 0.0f);
            }

            risposta ^= output_x;
            risposta ^= output_y1;
            risposta ^= output_y2;
            if(risposta) {
                ex ("Output invalido.", 0.0f);
            }
        }

    } else {
        //1. Controllo del tavolo scelto
        char output_table;
        do {
            output_table = safe_read<char> (fout);
        } while(output_table != 'T' && output_table != 'N');

        //2. Controllo della mossa
        uint32_t output_x, output_y1, output_y2;
        output_x = safe_read<uint32_t> (fout);
        //2.1 Controllo della scelta dell'X
        if(output_x == 0) {
            ex ("Output invalido. Il valore X non puo' essere zero", 0.0f);
        }
        if(output_table == input_table) {
            if(!(output_x == input_y1 || output_x == input_y2)) {
                if(N_Set.find(output_x) == N_Set.end()) {
                    ex ("Output invalido. Il valore X non e' nella lista", 0.0f);
                }
                if(output_x == input_x && N_Set[output_x] == 1) {
                    ex ("Output invalido. Il valore X non e' più presente nella lista per questo tavolo", 0.0f);
                }
            }
        } else {
            if(N_Set.find(output_x) == N_Set.end()) {
                ex ("Output invalido. Il valore X non era nella lista originale", 0.0f);
            }
        }
        //2.3 Controllo degli yi
        output_y1 = safe_read<uint32_t> (fout);
        output_y2 = safe_read<uint32_t> (fout);
        if(output_y1 + output_y2 >= output_x) {
            ex ("Output invalido. La somma degli yi deve essere inferiore ad X", 0.0f);
        }
        if(output_table == 'N') {
            if(output_y1 != 0 && output_y2 != 0) {
                ex ("Output invalido. Nel Nim almeno uno dei due yi deve essere zero", 0.0f);
            }
        }
        //2.4 Controllo della mossa vera e propria.
        uint32_t finePrimaMossa_1 = risposta, finePrimaMossa_2 = risposta;
        finePrimaMossa_1 ^= input_x;
        finePrimaMossa_1 ^= input_y1;
        finePrimaMossa_1 ^= input_y2;

        uint32_t cambiamento, invariato;
        if(output_table != input_table) {
            cambiamento = finePrimaMossa_2;
            invariato   = finePrimaMossa_1;
        } else {
            cambiamento = finePrimaMossa_1;
            invariato   = finePrimaMossa_2;
        }
        cambiamento ^= output_x;
        cambiamento ^= output_y1;
        cambiamento ^= output_y2;
        if(cambiamento ^ invariato) {
            ex ("Output invalido.", 0.0f);
        }
    }

	check_fine_file ();

	ex ("Corretto.", 1.0f);

	return 0;
}
