/*
 * GENERATORE task A_seq
 * Usage: ./generatore g n maxW seed
 *  g in {1,2} indica il goal
 *  n >= 1, la lunghezza della sequenza s
 *  0 <= minW <= maxW, gli n valori di s saranno tutti degli interi nell'intervallo chiuso [minW, maxW]
 */ 

#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
	assert(argc == 6);
	int g = atoi(argv[1]);
	int n = atoi(argv[2]);
	int minW = atoi(argv[3]);
	int maxW = atoi(argv[4]);
	int seed = atoi(argv[5]);
	srand(seed);
	cout << g << " " << n << endl;
	for (int i = 0; i < n; i++)
	  cout << minW + (rand() % (maxW-minW +1)) << " ";
	cout << endl;
	return 0;
}
