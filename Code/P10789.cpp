// Problem: P10789 [NOI2024] 登山
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10789
// Memory Limit: 2048 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-19 15:49:09
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
const int inf=1e9;
bool mbe;

inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,fa[maxn],dep[maxn];
vector<int> e[maxn];
int l[maxn],r[maxn],lim[maxn];
int to[maxn][17],val[maxn][17];
int jump(int u,int w){
	for(int i=16;~i;i--)if(val[u][i]>=w)u=to[u][i];
	if(lim[u]>=w)u=fa[u];
	return u;
}
void dfs1(int u){
	to[u][0]=fa[u],val[u][0]=lim[u];
	for(int j=1;j<=16;j++)to[u][j]=to[to[u][j-1]][j-1],val[u][j]=min(val[u][j-1],val[to[u][j-1]][j-1]);
	for(int v:e[u])dfs1(v);
}
vector<pii> upd[maxn];
int f[maxn];
int son[maxn];
void dfs2(int u){
	son[u]=0;
	for(int v:e[u]){
		dfs2(v);
		if(upd[v].size()>=upd[son[u]].size())son[u]=v;
	}
	if(!son[u])return ;
	swap(upd[u],upd[son[u]]);
	for(int v:e[u]){
		for(pii p:upd[v])upd[u].pb(p);
	}
}
int dp[maxn],sum[maxn],res;
void dfs3(int u){
	if(u==1)dp[u]=1;
	else dp[u]=res;
	inc(sum[dep[u]]=sum[dep[u]-1],dp[u]);
	if(!son[u])return ;
	for(int v:e[u])if(v!=son[u]){
		for(auto[d,w]:upd[v])inc(res,mod-1ll*w*sum[d]%mod);
	}
	for(auto[d,w]:upd[son[u]])inc(res,mod-1ll*w*sum[d]%mod);
	dfs3(son[u]);
	for(int v:e[u])if(v!=son[u]){
		res=0;for(auto[d,w]:upd[v])inc(res,w*sum[d]%mod);
		dfs3(v);
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)e[i].clear();
	lim[1]=-1;for(int i=2;i<=n;i++){
		fa[i]=read();dep[i]=dep[fa[i]]+1;e[fa[i]].pb(i);
		r[i]=dep[i]-read(),l[i]=dep[i]-read();
		lim[i]=dep[i]-read()-1;
	}
	dfs1(1);
	for(int i=1;i<=n;i++)f[i]=0,upd[i].clear();
	for(int i=2;i<=n;i++){
		int p1=jump(i,l[i]),p2=jump(i,r[i]);
		upd[i].pb({r[i],1}),upd[p2].pb({r[i],mod-1	});
		f[p2]++,f[p1]--;
		upd[i].pb({l[i]-1,mod-1}),upd[p1].pb({l[i]-1,1});
	}
	for(int i=n;i>1;i--){
		int p=jump(i,lim[i]);f[p]+=f[i];
		upd[i].pb({lim[i],f[i]}),upd[p].pb({lim[i],mod-f[i]});
	}
	dfs2(1);
	res=0;dfs3(1);
	for(int i=2;i<=n;i++)printf("%lld ",dp[i]);puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	read();T=read();
	while(T--)work();
}