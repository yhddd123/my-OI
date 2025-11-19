// Problem: CF1870H Standard Graph Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1870H
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-19 21:12:17
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
const int maxn=400010;
const int inf=1e12;
bool mbe;

int n,m,q;
struct bcj{
	int f[maxn];
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	void merge(int u,int v){f[fd(u)]=fd(v);}
	void init(){
		for(int i=1;i<=n;i++)f[i]=i;
	}
}f1,f2;
int fa[maxn],val[maxn],rt,idx;
namespace dmst{
priority_queue<pii,vector<pii>,greater<pii>> q[maxn];int tag[maxn];
void merge(int u,int v){
	if(q[u].size()<q[v].size())swap(q[u],q[v]),swap(tag[u],tag[v]);
	while(!q[v].empty()){
		pii p=q[v].top();q[v].pop();
		q[u].push({p.fi+tag[v]-tag[u],p.se});
	}
}
void sovle(){
	for(int i=1;i<=n;i++)q[i].push({inf,i%n+1});
	f1.init(),f2.init();
	queue<int> qq;
	for(int i=1;i<=n;i++)qq.push(i);
	while(!qq.empty()){
		int u=f1.fd(qq.front());qq.pop();
		while(q[u].size()&&u==f1.fd(q[u].top().se))q[u].pop();
		if(!q[u].size()){rt=u;break;}
		auto[w,v]=q[u].top();
		v=f1.fd(v),w+=tag[u];
		if(f2.fd(u)!=f2.fd(v)){
			f2.merge(u,v);
			fa[u]=v,val[u]=w;
		}
		else{
			++idx;qq.push(idx);f1.f[idx]=f2.f[idx]=idx;
			while(v!=u){
				tag[v]-=val[v];merge(idx,v);
				f1.merge(v,idx);
				int nw=f1.fd(fa[v]);
				fa[v]=idx;v=nw;
			}
			fa[u]=idx,val[u]=w;
			tag[u]-=val[u];merge(idx,u);
			f1.merge(u,idx);
			f2.merge(idx,u);
		}
	}
	// for(int i=1;i<=idx;i++)cout<<fa[i]<<" ";cout<<"\n";
	// for(int i=1;i<=idx;i++)cout<<f1.fd(i)<<" ";cout<<"\n";
	// for(int i=1;i<=idx;i++)cout<<f2.fd(i)<<" ";cout<<"\n";
	// cout<<rt<<"\n";
}
}
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int siz[maxn],son[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1;son[u]=0;dep[u]=dep[fa[u]]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],tim,tp[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++tim]=u,tp[u]=lst;
	if(son[u])dfs(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==son[u])continue;
		dfs(v,v);
	}
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2],sum[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){sum[nd]=val[rnk[l]];return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	sum[nd]=sum[ls]+sum[rs];
}
void up(int nd){
	mn[nd]=min(mn[ls],mn[rs]);
	sum[nd]=(mn[nd]==mn[ls])*sum[ls]+(mn[nd]==mn[rs])*sum[rs];
}
void upd(int nd,int w){mn[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	up(nd);
}
void mdf(int u,int w){
	while(u){
		updata(1,1,idx,dfn[tp[u]],dfn[u],w);
		u=fa[tp[u]];
	}
}
void work(){
	n=read();m=read();q=read();idx=n;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		dmst::q[u].push({w,v});
	}
	dmst::sovle();
	for(int i=1;i<=idx;i++)if(i!=rt)add(fa[i],i,val[i]);
	dfs(rt),dfs(rt,rt);
	build(1,1,idx);
	while(q--){
		char ch=getchar();while(ch!='-'&&ch!='+')ch=getchar();
		int p=read();
		mdf(p,(ch=='+')*2-1);
		int res=mn[1]?0:sum[1];
		if(res>=inf)res=-1;
		printf("%lld\n",res);
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