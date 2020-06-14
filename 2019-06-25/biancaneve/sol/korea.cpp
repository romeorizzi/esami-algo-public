#include <stdio.h>
#include <algorithm>
using namespace std;

const int Z = 262144;
int N,M,U[200002],MAX[Z*2],MIN[Z*2];

void in(int p, int x)
{
	 p += Z; MAX[p] = MIN[p] = x; p >>= 1;
	 while (p){
		 MAX[p] = max(MAX[p*2],MAX[p*2+1]);
		 MIN[p] = min(MIN[p*2],MIN[p*2+1]);
		 p >>= 1;
	 }
}

int out(int s, int e)
{
	s += Z; e += Z;
	int rmax=0,rmin=N+1;

	while (s < e){
		if (s & 1){
			rmax = max(rmax,MAX[s]);
			rmin = min(rmin,MIN[s]);
			s++;
		}

		if (~e & 1){
			rmax = max(rmax,MAX[e]);
			rmin = min(rmin,MIN[e]);
			e--;
		}

		s >>= 1; e >>= 1;
	}
	if (s == e){
		rmax = max(rmax,MAX[e]);
		rmin = min(rmin,MIN[e]);
	}

	return rmax - rmin;
}

int main()
{
	int i,o,x,y,t;

	scanf ("%d %d",&N,&M);
	for (i=1;i<=N;i++) scanf ("%d",&U[i]);
	for (i=1;i<=N;i++) MAX[U[i]+Z] = MIN[U[i]+Z] = i;
	for (i=Z-1;i>=1;i--){
		MAX[i] = max(MAX[i*2],MAX[i*2+1]);
		MIN[i] = min(MIN[i*2],MIN[i*2+1]);
	}

	while (M--){
		scanf ("%d %d %d",&o,&x,&y);

		if (o == 1){
			t = U[x]; U[x] = U[y]; U[y] = t;

			in(U[x],x);
			in(U[y],y);
		}
		else{
			puts(out(x,y)==(y-x)?"YES":"NO");
		}
	}

	return 0;
}
