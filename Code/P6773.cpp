// Problem: P6773 [NOI2020] 命运
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6773
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-01 20:58:05
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m;
vector<int> e[maxn],g[maxn];
int dep[maxn];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
const int maxm=maxn<<6;
int sum[maxm],tag[maxm],lc[maxm],rc[maxm],rt[maxn],idx;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void upd(int nd,int w){sum[nd]=1ll*sum[nd]*w%mod,tag[nd]=1ll*tag[nd]*w%mod;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=1;}
void modif(int &nd,int l,int r,int p,int w){
	if(!nd)nd=++idx,tag[nd]=1;
	if(l==r){
		sum[nd]=w;
		return ;
	}
	if(tag[nd]!=1)down(nd);
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	inc(sum[nd]=sum[ls],sum[rs]);
}
void updata(int &nd,int l,int r,int ql,int qr,int w){
	if(!nd)nd=++idx,tag[nd]=1;
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd]!=1)down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	inc(sum[nd]=sum[ls],sum[rs]);
}
int merge(int u,int v,int l,int r,int vu,int vv){
	if(!u){
		upd(v,vu);return v;
	}
	if(!v){
		upd(u,vv);return u;
	}
	if(l==r){
		inc(vv,sum[v]);
		inc(sum[u]=1ll*sum[u]*vv%mod,1ll*sum[v]*vu%mod);return u;
	}
	if(tag[u]!=1)down(u);
	if(tag[v]!=1)down(v);
	rc[u]=merge(rc[u],rc[v],mid+1,r,(vu+sum[lc[u]])%mod,(vv+sum[lc[v]])%mod);
	lc[u]=merge(lc[u],lc[v],l,mid,vu,vv);
	inc(sum[u]=sum[lc[u]],sum[rc[u]]);
	return u;
}
int query(int nd,int l,int r,int p){
	if(l==r)return sum[nd];
	if(tag[nd]!=1)down(nd);
	if(p<=mid)return query(ls,l,mid,p);
	else return query(rs,mid+1,r,p);
}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	int mx=0;for(int v:g[u])mx=max(mx,dep[v]);
	modif(rt[u],0,n,mx,1);
	for(int v:e[u]){
		if(v==fa)continue;dfs(v,u);
		rt[u]=merge(rt[u],rt[v],0,n,0,sum[rt[v]]);
	}
	updata(rt[u],0,n,dep[u],n,0);
	// cout<<u<<"\n";
	// for(int i=0;i<=n;i++)cout<<query(rt[u],0,n,i)<<" ";cout<<"\n";
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		g[v].pb(u);
	}
	dfs(1,0);
	printf("%d\n",sum[rt[1]]);
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