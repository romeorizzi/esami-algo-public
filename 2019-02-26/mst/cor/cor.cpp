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

struct arco
{
	int u;
	int v;
	int c;

	bool operator == (const arco& a) const
	{
		return (u == a.u) && (v == a.v);
	}

	bool operator < (const arco& a) const
	{
		if (u != a.u)
			return u < a.u;
		else
			return v < a.v;
	}
};

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
	int m = safe_read<int> (fin);
	set<arco> grafo; // Il grafo di input
	set<arco> albero; // L'albero da correggere

	arco a;
	for (int i = 0; i < m; i += 1)
	{
		a.u = safe_read<int> (fin, 0);
		a.v = safe_read<int> (fin, 0);
		a.c = safe_read<int> (fin, 0);
		if (a.u > a.v)
			swap (a.u, a.v);
		grafo.insert (a);
//		cout << a.u << " " << a.v << " " << a.c << endl;
	}

	for (int i = 0; i < n-1; i += 1)
	{
		a.u = safe_read<int> (fout, 0);
		a.v = safe_read<int> (fout, 0);
		if (a.u > a.v)
			swap (a.u, a.v);
		albero.insert (a);
//		cout << a.u << " " << a.v << endl;
	}

	vector<arco> result; // Gli archi in comune tra il grafo e l'albero
	back_insert_iterator< vector<arco> > ii (result);
	set_intersection (grafo.begin(), grafo.end(), albero.begin(), albero.end(), ii);

	if (result.size() != (unsigned int)(n-1)) // Devono essere N-1
	{
		ex ("Output malformato.", 0.0f);
	}
	
	int somma = 0;
	for (unsigned int i = 0; i < result.size(); i += 1)
	{
		somma += result[i].c;
	}

	if (somma != result_out) // La loro somma deve essere uguale a quella dichiarata
	{
		ex ("Output invalido.", 0.0f);
	}

	check_fine_file ();

	ex ("Corretto.", 1.0f);

	return 0;
}
