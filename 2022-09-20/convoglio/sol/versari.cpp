#include <cstdio>
#include <vector>
using namespace std;
vector<int> graph[200000];
int N,M;
int daddies[200000];
bool isancestor[200000];
vector<int> cycle;
int new_match[100000];
int dfs(int n,int d){
	daddies[n]=d+1;
	isancestor[n]=true;
	for(unsigned i=0;i<graph[n].size();i++){
		if(isancestor[graph[n][i]]){
			cycle.push_back(graph[n][i]);
			int t=n;
			cycle.push_back(t);
			while(t!=graph[n][i]){
				t=daddies[t]-1;
				cycle.push_back(t);
			}
			return true;
		}
		if(daddies[graph[n][i]]) continue;
		if(dfs(graph[n][i],n)) return true;
	}
	isancestor[n]=false;
	return false;
}
int main(){
  /*
#ifdef EVAL
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
  */
	int warn_unused_result = scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++){
		int a,b;
		warn_unused_result = scanf("%d%d",&a,&b);
		b+=N;
		if(i<N) graph[a].push_back(b);
		else graph[b].push_back(a);
	}
	for(int i=0;i<N;i++){
		while(i<N && daddies[i]) i++;
		if(i<N && dfs(i,i)){
			for(unsigned i=1;i<cycle.size();i++)
				if(cycle[i-1]<N)
					new_match[cycle[i-1]]=cycle[i];
			for(int i=0;i<N;i++)
				if(!new_match[i])
					new_match[i]=graph[i][0];
			for(int i=0;i<N;i++) printf("%d %d\n",i,new_match[i]-N);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
