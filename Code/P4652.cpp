// Problem: P4652 [CEOI2017] One-Way Streets
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4652
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
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

int n,m,q;
int head[maxn],tot=1;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
vector<int> g[maxn];
int dfn[maxn],idx,lw[maxn];
int st[maxn],tp;
int scc[maxn],scct;
bool vis[maxn];
void tar(int u,int fl){
	dfn[u]=lw[u]=++idx;
	st[++tp]=u;vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(i==(fl^1))continue;
		if(!dfn[v]){
			tar(v,i);
			lw[u]=min(lw[u],lw[v]);
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		scc[st[tp]]=++scct;
		vis[st[tp]]=0;
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			vis[st[tp]]=0;
		}
	}
}
int f[maxn];
int to[maxn][17],dep[maxn];
void dfs(int u,int fa){
	to[u][0]=fa;dep[u]=dep[fa]+1;
	for(int i=1;i<=16;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int v:g[u]){
		if(v==fa)continue;
		dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=16;~i;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=16;~i;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
vector<int> p;
void dfs1(int u,int fa){
	for(int v:g[u]){
		if(v==fa)continue;
		dfs1(v,u);
		f[u]+=f[v];
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i,0);
	for(int i=2;i<=tot;i+=2){
		int u=e[i].to,v=e[i^1].to;
		if(scc[u]!=scc[v])g[scc[u]].push_back(scc[v]),g[scc[v]].push_back(scc[u]);
	}
	// for(int i=1;i<=n;i++)cout<<scc[i]<<" ";cout<<"\n";
	// for(int i=1;i<=scct;i++){
		// for(int j:g[i])cout<<i<<" "<<j<<"\n";
	// }
	for(int i=1;i<=scct;i++)if(!dep[i])dfs(i,0),p.push_back(i);
	q=read();
	while(q--){
		int u=read(),v=read();
		// cout<<scc[u]<<" "<<scc[v]<<"\n";
		if(scc[u]==scc[v])continue;
		else{
			u=scc[u],v=scc[v];int tp=lca(u,v);	
			f[u]++,f[tp]--;f[v]--,f[tp]++;
		}
	}
	// for(int i=1;i<=scct;i++)cout<<f[i]<<" ";cout<<"\n";
	for(int i:p)dfs1(i,0);
	for(int i=2;i<=tot;i+=2){
		int u=e[i^1].to,v=e[i].to;
		if(scc[u]==scc[v])printf("B");
		else{
			u=scc[u],v=scc[v];
			if(dep[u]<dep[v]){
				if(f[v]>0)printf("L");
				if(!f[v])printf("B");
				if(f[v]<0)printf("R");
			}
			else{
				if(f[u]>0)printf("R");
				if(!f[u])printf("B");
				if(f[u]<0)printf("L");
			}
		}
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
