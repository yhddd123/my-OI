// Problem: CF1336F Journey
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1336F
// Memory Limit: 1000 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-12-10 18:23:44
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
const int maxn=150010;
const int inf=1e9;
bool mbe;

int n,m,k,ans;
pii a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],son[maxn],fa[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1,son[u]=0;dep[u]=dep[fa[u]]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++tim]=u;tp[u]=lst;
	if(!son[u])return ;
	dfs(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs(v,v);
	}
}
int lca(int u,int v){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	return v;
}
bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
int kth(int u,int k){
	while(dep[u]-dep[fa[tp[u]]]<=k){
		k-=dep[u]-dep[fa[tp[u]]];
		u=fa[tp[u]];
	}
	return rnk[dfn[u]-k+1];
}
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
int que(int l,int r){return que(r)-que(l-1);}
vector<int> add[maxn],del[maxn];
void dfs1(int u){
	
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int i=1;i<=m;i++)a[i]={read(),read()};
	dfs(1),dfs(1,1);
	for(int i=1;i<=m;i++){
		add[a[i].fi].pb(i),add[a[i].se].pb(i),del[lca(a[i].fi,a[i].se)].pb(i);
	}
	dfs1(1);
	printf("%lld\n",ans);
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