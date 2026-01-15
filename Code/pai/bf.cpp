// Problem: P12703 [KOI 2022 Round 2] 外环路
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12703
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2026-01-15 18:23:37
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=100010;
const int maxq=250010;
const int inf=1e18;
bool mbe;

int n,k,q;
int ans[maxq];
vector<pii> e[maxn],g[maxn];
int in[maxn],out[maxn],id[maxn];
void dfs(int u,int fa){
	if(e[u].size()==1)id[k]=u,in[u]=k++;
	for(auto[v,w]:e[u])if(v!=fa){
		dfs(v,u);
	}
	out[u]=k-1;
}
int dis[maxn];
bool bk[maxn];
void work(){
	n=read();
	for(int i=2;i<=n;i++){
		int u=read(),w=read();
		e[u].pb({i,w}),e[i].pb({u,w});
	}
	dfs(1,0);
	for(int i=0;i<k;i++){
		int w=read();
		g[id[i]].pb({id[(i+1)%k],w}),g[id[(i+1)%k]].pb({id[i],w});
	}
	q=read();
	for(int i=1;i<=q;i++){
		int u=read(),v=read();
		for(int u=1;u<=n;u++)dis[u]=inf,bk[u]=0;
		priority_queue<pii> q;
		dis[u]=0;q.push({-dis[u],u});
		while(!q.empty()){
			int u=q.top().se;q.pop();
			if(bk[u])continue;bk[u]=1;
			for(auto[v,w]:e[u]){
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					q.push({-dis[v],v});
				}
			}
			for(auto[v,w]:g[u]){
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					q.push({-dis[v],v});
				}
			}
		}
		cout<<dis[v]<<"\n";
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}