#include <cassert>
#include <cstdio>
using namespace std;

const int MAXM=200000, MAXN=100000;
int N,M;

int main(){
	scanf("%d%d",&N,&M);
	assert(M >= 2);
	assert(M <= MAXM);
	assert(N >= 2);
	assert(N < MAXN);
	//printf("N=%d, M=%d\n",N,M);
	for(int i=0;i<M;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		assert(a >= 0);
		assert(a < N);
		assert(b >= 0);
		assert(b < N);
		//printf("message=%d, ship=%d\n",a,b);
	}
	printf("-1\n");
	return 0;
}
