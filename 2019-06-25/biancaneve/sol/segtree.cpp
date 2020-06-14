#include <cstdio>
#include <algorithm>

#define MAXN 300000
#define INF 100000000

using namespace std;

struct node {
	int minim,maxim;
};

node segtree[ 4*MAXN + 1 ];

void init( int n,int i,int j,int* A )
{
	if( i == j ) {
		segtree[ n ].minim = A[ i ];
		segtree[ n ].maxim = A[ i ];
	} else {
		init( 2*n, i, ( i + j ) / 2, A );
		init( 2*n + 1,( i + j ) / 2 + 1, j, A );
		segtree[ n ].maxim = max( segtree[ 2*n ].maxim, segtree[ 2*n + 1 ].maxim );
		segtree[ n ].minim = min( segtree[ 2*n ].minim, segtree[ 2*n + 1 ].minim );
	}
}

void update( int i,int l,int r,int idx,int val )
{
	if( l == r && l == idx ) {
		segtree[ i ].maxim = val;
		segtree[ i ].minim = val;
		return;
	}
	else if( idx <= ( l + r ) / 2 ) {
		update( 2*i,l,( l + r ) / 2,idx,val);
	}
	else if( idx > ( l + r ) / 2 ) {
		update( 2*i + 1,( l + r ) / 2 + 1,r,idx,val );	
	}
	segtree[ i ].maxim = max( segtree[ 2*i ].maxim, segtree[ 2*i + 1 ].maxim );
	segtree[ i ].minim = min( segtree[ 2*i ].minim, segtree[ 2*i + 1 ].minim );
}

int maxquery(int n,int l,int r,int i,int j)  
{  
    if(l > j || r < i) {  
        return 0;  
    }  
    else if( i <= l && r <= j ) {  
        return segtree[ n ].maxim;  
    } else {  
        return max(maxquery(2*n,l,( l + r ) / 2,i,j), maxquery(2*n+1,( l + r ) /2 + 1,r,i,j) );  
    }  
}  
  
int minquery(int n,int l,int r,int i,int j)  
{  
    if( l > j || r < i ) {  
        return INF;  
    }  
    else if( i <= l && r <= j ) {  
        return segtree[ n ].minim;  
    } else {  
        return min(minquery(2*n,l,( l + r ) /2,i,j) , minquery(2*n + 1,(l + r ) / 2 + 1, r, i ,j ) );  
    }  
}

int main( void )
{
	int N,Q,u,v,w;
	scanf("%d%d",&N,&Q);
	int A[ N + 1 ],Anew[ N + 1 ];
	for( int i = 1; i <= N; i++ ) {
		scanf("%d",&u);
		A[ u ] = i;
		Anew[ i ] = u;
	}
	init( 1,1,N,A );
	while( Q-- ) {
		scanf("%d%d%d",&u,&v,&w);
		if( u == 1 ) {
			int pv = Anew[ v ];
			int pw = Anew[ w ];
			swap( A[ pv ], A[ pw ] );
			swap( Anew[ v ],Anew[ w ] );
			update( 1,1,N, pv,w );
			update( 1,1,N, pw,v );
		} else {
			int maxim = maxquery( 1,1,N,v,w );
			int minim = minquery( 1,1,N,v,w );
			if( maxim - minim == w-v ) {
				printf("YES\n");
			} else {
				printf("NO\n");	
			}
		}
	}
	return 0;
}
