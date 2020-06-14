#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAXN 200010
typedef long long int LL;
typedef unsigned long long int ULL;
using namespace std;

const int pp=1<<18;
const int inf=1e8;

int N,M;
int aa[MAXN];
int pos[MAXN];
int mi[2*pp+10];
int ma[2*pp+10];
int ll[2*pp+10];
int rr[2*pp+10];

void init(int v){
	if (v>=pp) ll[v]=rr[v]=v-pp;
	else {
		init(2*v),init(2*v+1);
		ll[v]=ll[2*v],rr[v]=rr[2*v+1];
	}
}

void update(int v,int x,int val){
	if (x<ll[v] or rr[v]<x) return;
	if (x==ll[v] and x==rr[v]) {
		ma[v]=mi[v]=val;
		return;
	}
	update(2*v,x,val);
	update(2*v+1,x,val);
	ma[v]=max(ma[2*v],ma[2*v+1]);
	mi[v]=min(mi[2*v],mi[2*v+1]);
}

void swappa(int x,int y){
	int a=aa[x],b=aa[y];
	update(1,b,x);
	update(1,a,y);
	aa[x]=b,aa[y]=a;
	pos[a]=y,pos[b]=x;
}

int minore(int v,int ii,int ff){
	if (ff<ll[v] or rr[v]<ii) return inf;
	if (ii<=ll[v] and rr[v]<=ff) return mi[v];
	return min(minore(2*v,ii,ff),minore(2*v+1,ii,ff));
}

int maggiore(int v,int ii,int ff){
	if (ff<ll[v] or rr[v]<ii) return 0;
	if (ii<=ll[v] and rr[v]<=ff) return ma[v];
	return max(maggiore(2*v,ii,ff),maggiore(2*v+1,ii,ff));
}

int main(){
	init(1);
	cin >> N >> M;
	for (int i=1; i<=N; i++) {
		cin >> aa[i];
		pos[aa[i]]=i;
		update(1,aa[i],i);
	}
	for (int i=0; i<M; i++) {
		int t;
		cin >> t;
		if (t==1) {
			int x,y;
			cin >> x >> y;
			swappa(x,y);
		}
		if (t==2) {
			int a,b;
			cin >> a >> b;
			int mm=minore(1,a,b);
			int MM=maggiore(1,a,b);
			if (MM-mm==b-a) cout << "YES\n";
			else cout << "NO\n";
		}
	}
}
