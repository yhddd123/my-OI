// Problem: P4617 [COCI2017-2018#5] Planinarenje
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4617
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-09 21:10:55
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int s,t;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int dis[maxn],rad[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	dis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w)dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out,e[i^1].w+=out;
			res-=out,cnt+=out;
			if(!res)break;
		}
	}
	return cnt;
}
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int scc[maxn],scct;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!e[i].w)continue;
		if(!dfn[v])tar(v),lw[u]=min(lw[u],lw[v]);
		else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		scc[st[tp]]=++scct;
		while(st[tp--]!=u)scc[st[tp]]=scct;
	}
}
void work(){
	n=read();m=read();s=2*n+1,t=2*n+2;
	for(int i=1;i<=n;i++)add(s,i,1);
	for(int i=1;i<=n;i++)add(i+n,t,1);
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v+n,1);
	}
	int flow=0;while(bfs())flow+=dfs(s,inf);
	for(int i=1;i<=t;i++)if(!dfn[i])tar(i);
	// for(int i=1;i<=n;i++)cout<<scc[i]<<" ";cout<<"\n";cout<<scc[s]<<"\n";
	for(int i=1;i<=n;i++){
		if(scc[i]!=scc[s]&&!e[i*2].w)puts("Slavko");
		else puts("Mirko");
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
