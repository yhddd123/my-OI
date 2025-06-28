#include<bits/stdc++.h>
#include "swap.h"

using namespace std;
const int maxn=400010;
#define pb push_back

int n,m,idx;
tuple<int,int,int> g[maxn];
int f[maxn],val[maxn];
bool vis[maxn];
int hd[maxn],ed[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
vector<int> e[maxn];
int dep[maxn],to[maxn][19];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1,to[u][0]=fa;
	for(int i=1;i<=18;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int v:e[u])dfs(v,u);
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=18;~i;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=18;~i;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
int get(int u){
	if(vis[u])return u;
	for(int i=18;~i;i--)if(!vis[to[u][i]])u=to[u][i];
	return to[u][0];
}
void init(int N, int M, vector<int> U, vector<int> V, vector<int> W) {
	n=N,m=M;
	for(int i=1;i<=m;i++)g[i]={W[i-1],U[i-1]+1,V[i-1]+1};
	sort(g+1,g+m+1);
	for(int i=1;i<=n;i++)f[i]=i,hd[i]=ed[i]=i;idx=n;vis[0]=1,val[0]=-1;
	for(int i=1;i<=m;i++){
		auto[w,x,y]=g[i];
		int u=fd(x),v=fd(y);
		if(u==v){
			if(!vis[i]){
				++idx,f[idx]=idx,vis[idx]=1,val[idx]=w;
				f[u]=idx;e[idx].pb(u);
			}
		}
		else{
			if(hd[u]==x)swap(hd[u],ed[u]);
			if(ed[v]==y)swap(hd[v],ed[v]);
			if(!vis[u]&&!vis[v]&&ed[u]==x&&hd[v]==y){
				// cout<<x<<" "<<y<<"\n";
				++idx;f[idx]=idx,vis[idx]=0,val[idx]=w;
				f[u]=f[v]=idx;e[idx].pb(u),e[idx].pb(v);
				hd[idx]=hd[u],ed[idx]=ed[v];
			}
			else{
				++idx;f[idx]=idx,vis[idx]=1,val[idx]=w;
				f[u]=f[v]=idx;e[idx].pb(u),e[idx].pb(v);
			}
		}
	}
	for(int i=1;i<=idx;i++)if(f[i]==i)e[0].pb(i);
	// for(int i=1;i<=idx;i++)cout<<i<<" "<<f[i]<<" "<<vis[i]<<" "<<val[i]<<"\n";
	dfs(0,0);
}
int getMinimumFuelCapacity(int X, int Y) {
	int u=X+1,v=Y+1;
	// cout<<u<<" "<<v<<" "<<lca(u,v)<<"\n";
	return val[get(lca(u,v))];
}

// int main() {
  // int N, M;
  // assert(2 == scanf("%d %d", &N, &M));
//   
  // std::vector<int> U(M), V(M), W(M);
  // for (int i = 0; i < M; ++i) {
    // assert(3 == scanf("%d %d %d", &U[i], &V[i], &W[i]));
  // }
// 
  // int Q;
  // assert(1 == scanf("%d", &Q));
// 
  // std::vector<int> X(Q), Y(Q);
  // for (int i = 0; i < Q; ++i) {
    // assert(2 == scanf("%d %d", &X[i], &Y[i]));
  // }
// 
  // init(N, M, U, V, W);
//   
  // std::vector<int> minimum_fuel_capacities(Q);
  // for (int i = 0; i < Q; ++i) {
    // minimum_fuel_capacities[i] = getMinimumFuelCapacity(X[i], Y[i]);
  // }
// 
  // for (int i = 0; i < Q; ++i) {
    // printf("%d\n", minimum_fuel_capacities[i]);
  // }
//   
  // return 0;
// }