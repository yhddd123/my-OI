// Problem: P9432 [NAPC-#1] rStage5 - Hard Conveyors
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9432
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-04-17 16:58:36
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,p,k;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dis[maxn];bool vis[maxn];
priority_queue<pii> q;
int to[17][maxn],w[17][maxn],d[maxn],dep[maxn];
void dfs(int u,int fa){
	to[0][u]=fa,w[0][u]=dis[u],dep[u]=dep[fa]+1;
	for(int i=1;i<=16;i++)to[i][u]=to[i-1][to[i-1][u]],w[i][u]=min(w[i-1][u],w[i-1][to[i-1][u]]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		d[v]=d[u]+e[i].w;dfs(v,u);
	}
}
int lca(int u,int v){
	int uu=u,vv=v;
	if(dep[u]<dep[v])swap(u,v);
	int res=inf;
	for(int i=16;~i;i--)if(dep[to[i][u]]>=dep[v])res=min(res,w[i][u]),u=to[i][u];
	// cout<<d[uu]+d[vv]-d[u]*2<<" "<<res<<" "<<dis[u]<<"\n";
	if(u==v)return d[uu]+d[vv]-d[u]*2+min(res,dis[u])*2;
	for(int i=16;~i;i--)if(to[i][u]!=to[i][v])res=min({res,w[i][u],w[i][v]}),u=to[i][u],v=to[i][v];
	res=min({res,w[0][u],w[0][v]});u=to[0][u];
	// cout<<u<<" "<<res<<"\n";
	return d[uu]+d[vv]-d[u]*2+min(res,dis[u])*2;
}
void work(){
	n=read();p=read();k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	mems(dis,0x3f);
	for(int i=1;i<=k;i++){
		int x=read();
		dis[x]=0;q.push({0,x});
	}
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				q.push({-dis[v],v});
			}
		}
	}
	// for(int i=1;i<=n;i++)cout<<dis[i]<<" ";cout<<"\n";
	dfs(1,0);
	while(p--){
		int u=read(),v=read();
		printf("%lld\n",lca(u,v));
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
