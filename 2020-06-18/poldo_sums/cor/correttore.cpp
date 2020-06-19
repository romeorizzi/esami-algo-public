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
	if (source.fail () || source.eof ())
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

	int result_cor = safe_read<int> (fcor);
	int result_out = safe_read<int> (fout, 0);

	if (result_cor != result_out) // Il risultato deve essere uguale
	{
		ex ("Output invalido.", 0.0f);
	}

	int n = safe_read<int> (fin);

	vector<int> P(n), G(n);

	for (int i = 0; i < n; i++) {
		P[i] = safe_read<int> (fin, 0);
		G[i] = safe_read<int> (fin, -10000);
	}

    int prev = safe_read<int> (fout, 0);
	for (int i = 1; i < result_cor; i++)
	{
        int cur = safe_read<int> (fout, prev + 1, n);

        int sum = 0;
        for (int j = prev; j < cur; j++) {
            sum += G[j];
        }

        if (sum + P[prev] > P[cur]) {
            ex("Equazione fondamentale non rispettata.", 0.0f);
        }
    }

	check_fine_file ();

	ex ("Corretto.", 1.0f);

	return 0;
}
