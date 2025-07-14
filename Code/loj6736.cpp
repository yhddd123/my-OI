// Problem: #6736. 「2020 集训队论文」最小连通块
// Contest: LibreOJ
// URL: https://loj.ac/p/6736
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2024-08-16 20:27:50
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#include"C.hpp"
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1010;

// namespace panole{
// const int N=5005;
// int n,i,j,x,y;
// std::vector<int>e[N];
// int f[20][N],eucnt,lo[N],id[N],ri[N];
// void dfs(int u,int fa){
	// f[0][id[u]=++eucnt]=u;
	// for(int i=0;i<e[u].size();++i)if(e[u][i]!=fa)dfs(e[u][i],u),f[0][++eucnt]=u;ri[u]=eucnt;
// }
// inline int cmp(int x,int y){return id[x]<id[y]?x:y;}
// inline int lca(int x,int y){
	// x=id[x];y=id[y];int l=lo[y-x+1];
	// return cmp(f[l][x],f[l][y-(1<<l)+1]);
// }
// std::vector<std::pair<int,int> >E;
// inline void ini(){
	// for(i=2;i<N;++i)lo[i]=lo[i>>1]+1;
	// scanf("%d",&n);
	// for(i=1;i<n;++i)scanf("%d%d",&x,&y),e[x].push_back(y),e[y].push_back(x),
		// E.push_back(std::make_pair(x,y));
	// dfs(1,0);
	// for(i=1;1<<i<=eucnt;++i)
		// for(j=1;j+(1<<i)-1<=eucnt;++j)f[i][j]=cmp(f[i-1][j],f[i-1][j+(1<<(i-1))]);
// }
// inline bool isanc(int x,int y){return id[x]<=id[y] && id[y]<=ri[x];}
// int S1,S2;
// inline bool ask(std::vector<int>a,int x){
	// S1++;S2+=a.size();
	// if(a.empty()){
		// puts("The set of query vertices is empty!");
		// exit(0);
	// }
	// int i,u=a[0],v=a[0];
	// bool flag=0;
	// if(x<1 || x>n){
		// puts("Invalid vertex!");
		// exit(0);		
	// }
	// for(i=0;i<a.size();++i){
		// if(a[i]<1 || a[i]>n){
			// puts("Invalid vertex!");
			// exit(0);
		// }
		// if(id[a[i]]<id[u])u=a[i];
		// if(id[v]<id[a[i]])v=a[i];
		// if(isanc(x,a[i]))flag=1;
	// }
	// u=lca(u,v);
	// return !isanc(u,x)?0:flag;
// }
// inline void check(std::vector<std::pair<int,int> >a){
	// int i;
	// if(a.size()!=n-1){
		// puts("The size of edge isn't n-1");
		// exit(0);
	// }
	// for(i=0;i<n-1;++i){
		// if(a[i].first>a[i].second)std::swap(a[i].first,a[i].second);
		// if(E[i].first>E[i].second)std::swap(E[i].first,E[i].second);
	// }
	// std::sort(a.begin(),a.end());
	// std::sort(E.begin(),E.end());
	// for(i=0;i<n-1;++i)if(a[i]!=E[i]){
		// puts("Your answer is wrong");
		// exit(0);
	// }
	// printf("Your answer is correct.You made %d queries with total size %d.\n",S1,S2);
// }
// }
// bool ask(std::vector<int>a,int x){return panole::ask(a,x);}
// std::vector<std::pair<int,int> >work(int n);

int n;
bool vis[maxn];
int fa[maxn];
void sovle(int u){
	vis[u]=1;
	while(1){
		vector<int> id;
		for(int i=1;i<=n;i++)if(!vis[i])id.push_back(i);
		id.push_back(1);
		if(!ask(id,u))break;
		id.pop_back();
		int l=0,r=id.size()-1;
		while(l<r){
			int mid=l+r>>1;
			vector<int> que;
			for(int i=l;i<=mid;i++)que.push_back(id[i]);
			que.push_back(1);
			if(ask(que,u))r=mid;
			else l=mid+1;
		}
		if(l>=id.size())break;
		sovle(id[l]);
	}
	while(1){
		vector<int> id;
		for(int i=2;i<=n;i++)if(!fa[i]&&i!=u)id.push_back(i);
		id.push_back(1);
		if(!ask(id,u))break;
		id.pop_back();
		int l=0,r=id.size()-1;
		while(l<r){
			int mid=l+r>>1;
			vector<int> que;
			for(int i=l;i<=mid;i++)que.push_back(id[i]);
			que.push_back(1);
			if(ask(que,u))r=mid;
			else l=mid+1;
		}
		if(l>=id.size())break;
		fa[id[l]]=u;
		// cout<<id[l]<<" "<<u<<"\n";
	}
}
vector<pii>work(int _n){
	n=_n;sovle(1);
	vector<pii> res;
	for(int i=2;i<=n;i++)res.push_back({i,fa[i]});
	return res;
}

// int main(){
	// panole::ini();
	// panole::check(work(panole::n));	
	// return 0;
// }