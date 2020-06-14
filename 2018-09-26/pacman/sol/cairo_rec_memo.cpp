#include <cassert>
#include <cstdio>
#include <algorithm>

const int BASE = 1000000;
const int MAXBLUE = 5;
const int MAXM = 500;
const int MAXN = 500;

int M, N;

char grid[MAXM][MAXM];

bool cached[MAXM][MAXM][MAXBLUE+1];
int cache[MAXM][MAXM][MAXBLUE+1];

int count(int i, int j, int b);

int cached_count(int i, int j, int b) {
	assert(0 <= b && b <= MAXBLUE);

	if (i == M || j == N)
		return 0;

	assert(0 <= i && i < M);
	assert(0 <= j && j < N);

	if(!cached[i][j][b]) {
		cache[i][j][b] = count(i, j, b);
		cached[i][j][b] = true;
		fprintf(stderr, "cache[%d][%d][%d] = %d\n", i, j, b, cache[i][j][b]);
	}

	return cache[i][j][b];
}

int count(int i, int j, int b)
{
	assert(0 <= i && i < M);
	assert(0 <= j && j < N);

	char g = grid[i][j];
	if (g == '#')
		return 0;
	if (g == '*' && b == 0)
		return 0;
	if (i == M - 1 && j == N - 1)
		return 1;
		
	int bonus = 0;
	if (g >= '1' && g <= '5')
		bonus = g - '0';
	b = std::max(b - 1, bonus);

	return (cached_count(i + 1, j, b) + cached_count(i, j + 1, b)) % BASE;
}

int main()
{
#ifdef EVAL
	assert(freopen("input.txt", "r", stdin));
	assert(freopen("output.txt", "w", stdout));
#endif
	scanf("%d%d", &M, &N);

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			scanf(" %c", &grid[i][j]);

	printf("%d\n", cached_count(0, 0, 0));
}
