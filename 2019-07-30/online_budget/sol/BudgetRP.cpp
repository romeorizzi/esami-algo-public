/**
 *  Template per soluzione in c++ per il problema online_budget
 *
 *  Autore: Romeo Rizzi, 2019-07-28
 *
 */

#include <cassert>
#include <iostream>
using namespace std;

const int MAX_N = 500;
const int MAX_VAL = 10;

int n, B0, x[MAX_N];

/*template <class T>
void print_array(T* v, int len)
{
	for (int i = 0; i < len; i++)
		cout << v[i] << " ";

	cout << endl;
}*/

int sumFib(int n)
{
	int s = 0;

	while (n > 0)
	{
		s += n;
		n--;
	}
	return s;
}

int calcS()
{
	int s = 1;

	for (int i = 0; i < n; i++)
	{
		s *= ((sumFib(B0) + 1) * x[i] + 1);
	}

	return s;
}

int main()
{
	cin >> n >> B0;

	for (int i = 0; i < n; i++)
		cin >> x[i];

	//print_array(x, n);

	cout << calcS() << endl;

	return 0;
}
