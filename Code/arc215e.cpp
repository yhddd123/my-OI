// Problem: E - CNOT Party
// Contest: AtCoder - AtCoder Regular Contest 215
// URL: https://atcoder.jp/contests/arc215/tasks/arc215_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-22 21:33:30
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m;
vector<pii> e[maxn],g[maxn];
int bk[maxn];
char a[maxn],b[maxn];
vector<int> ans;
bool vis[maxn];
vector<int> id;
void dfs(int u){
	vis[u]=1,id.pb(u);
	for(auto[v,i]:e[u]){
		if(!vis[v])dfs(v);
	}
	for(auto[v,i]:g[u]){
		if(!vis[v])dfs(v);
	}
}
int dfn[maxn],lw[maxn],tim;
int st[maxn],tp;
int scc[maxn],d[maxn],scct;
void tar(int u){
	dfn[u]=lw[u]=++tim;st[++tp]=u;
	for(auto[v,i]:e[u]){
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
	if(lw[u]==dfn[u]){
		scc[st[tp]]=++scct;
		while(st[tp--]!=u)scc[st[tp]]=scct;
	}
}
void dfs1(int u){
	vis[u]=1;
	for(auto[v,i]:e[u]){
		if(!vis[v]){
			if(a[u]=='1'&&a[v]=='0')ans.pb(i),a[v]='1';
			dfs1(v);
		}
	}
}
void dfs2(int u){
	vis[u]=1;
	for(auto[v,i]:e[u]){
		if(!vis[v]){
			dfs2(v);
			if(a[u]=='1'&&a[v]!=b[v])ans.pb(i),a[v]=b[v];
		}
	}
	if(a[u]=='1'&&b[u]=='0'&&bk[u])a[u]=b[u],ans.pb(bk[u]);
}
void sovle(int rt){
	id.clear();
	dfs(rt);
	tim=0,scct=0;for(int u:id)dfn[u]=0;
	for(int u:id)if(!dfn[u])tar(u);
	for(int i=1;i<=scct;i++)d[i]=0;
	for(int u:id){
		for(auto[v,i]:e[u]){
			if(scc[u]!=scc[v])d[scc[v]]++;
		}
	}
	for(int u:id)vis[u]=0;
	for(int u:id)if(a[u]=='1'&&!vis[u])dfs1(u);
	for(int u:id)vis[u]=0;
	for(int u:id)if((a[u]=='1'&&(b[u]=='1'||bk[u]))&&!vis[u])dfs2(u);
	for(int u:id)vis[u]=1;
	// for(int i=1;i<=n;i++)cout<<a[i];cout<<"\n";
}
void work(){
	n=read();scanf("%s%s",a+1,b+1);ans.clear();
	for(int i=1;i<=n;i++)e[i].clear(),g[i].clear(),bk[i]=0;
	m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb({v,i}),g[v].pb({u,i});
		if(u==v)bk[u]=i;
	}
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++)if(!vis[i])sovle(i);
	for(int i=1;i<=n;i++)if(a[i]!=b[i]){puts("-1");return ;}
	printf("%d\n",ans.size());
	for(int v:ans)printf("%d ",v);puts("");	
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}