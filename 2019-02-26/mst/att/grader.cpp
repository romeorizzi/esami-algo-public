#include <cstdio>
#include <cassert>
#include <cstdlib>

static FILE *fr, *fw;

// Declaring variables
static int N;
static int M;
static int* A;
static int* B;
static int* P;
static int* C;
static int* D;
static int minimo;

// Declaring functions
int mst(int N, int M, int* A, int* B, int* P, int* C, int* D);

int main() {
	fr = stdin;
	fw = stdout;

	// Reading input
	fscanf(fr, " %d %d", &N, &M);
	A = (int*)malloc((M) * sizeof(int));
	B = (int*)malloc((M) * sizeof(int));
	P = (int*)malloc((M) * sizeof(int));
	for (int i0 = 0; i0 < M; i0++) {
		fscanf(fr, " %d %d %d", &A[i0], &B[i0], &P[i0]);
	}

	// Calling functions
	C = (int*)malloc((N-1) * sizeof(int));
	D = (int*)malloc((N-1) * sizeof(int));
	minimo = mst(N, M, A, B, P, C, D);

	// Writing output
	fprintf(fw, "%d\n", minimo);
	for (int i0 = 0; i0 < N-1; i0++) {
		fprintf(fw, "%d %d\n", C[i0], D[i0]);
	}

	fclose(fr);
	fclose(fw);
	return 0;
}
