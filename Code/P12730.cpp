// Problem: P12730 [KOI 2021 Round 2] 美食推荐
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12730
// Memory Limit: 1024 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2025-06-08 21:53:38
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int to[maxn][17],dep[maxn];
int st[17][maxn],dfn[maxn],idx;
void dfs(int u,int fa){
	st[0][dfn[u]=++idx]=fa;
	to[u][0]=fa;dep[u]=dep[fa]+1;
	for(int i=1;i<=16;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
	}
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
int kth(int u,int k){
	for(int i=16;~i;i--)if(k&(1<<i))u=to[u][i];
	return !u?1:u;
}
bool vis[maxn];
int siz[maxn],w[maxn],sum,rt;
void getrt(int u,int fa){
	siz[u]=1,w[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		getrt(v,u);siz[u]+=siz[v];w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)rt=u;
}
int fa[maxn];
void sovle(int u){
	vis[u]=1;getrt(u,0);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		sum=siz[v];getrt(v,u);fa[rt]=u;sovle(rt);
	}
}
unordered_map<int,ll> f[maxn],g[maxn];
vector<tuple<int,int,int>> ask[maxn];
ll dp[maxn];
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==to[u][0])continue;
		dfs(v);dp[u]+=dp[v];
	}
	for(auto[p,d,w]:ask[u]){
		ll sum=0;int x=p;while(x){
			if(f[x].find(d+1-dis(x,p))!=f[x].end())sum+=f[x][d+1-dis(x,p)];
			x=fa[x];
		}
		x=p;while(fa[x]){
			if(g[x].find(d+1-dis(fa[x],p))!=g[x].end())sum-=g[x][d+1-dis(fa[x],p)];
			x=fa[x];
		}
		// cout<<u<<" "<<p<<" "<<sum<<" "<<w<<"\n";
		dp[u]=max(dp[u],sum+w);
	}
	int x=u;while(x)f[x][dis(x,u)]+=dp[u],x=fa[x];
	x=u;while(fa[x])g[x][dis(fa[x],u)]+=dp[u],x=fa[x];
	// cout<<u<<" "<<dp[u]<<"\n";
}
void work(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	for(int j=1;j<=16;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=m;i++){
		int p=read(),d=read(),w=read();
		ask[kth(p,d)].pb({p,d,w});
	}
	sum=n;getrt(1,0);sovle(rt);
	dfs(1);
	printf("%lld\n",dp[1]);
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