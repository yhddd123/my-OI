// Problem: P10145 [WC2024] 线段树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10145
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-10-17 14:59:58
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ull unsigned long long
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
bool mbe;

int n,m;
int lc[maxn],rc[maxn],md[maxn],pl[maxn],pr[maxn],idx;
int dfs(int l,int r){
	if(l+1==r){
		pl[++idx]=l,pr[idx]=r;
		return idx;
	}
	int mid=md[++idx]=read();pl[idx]=l,pr[idx]=r;
	int tmp=idx;
	// cout<<l<<" "<<r<<" "<<md[idx]<<endl;
	lc[tmp]=dfs(l,mid),rc[tmp]=dfs(mid,r);
	return tmp;
}
ull hsh[maxn];
mt19937_64 rnd(time(0));
pii a[maxn];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int rt[maxn];
namespace sgt{
	int tree[maxn<<6],tag[maxn<<6],lc[maxn<<6],rc[maxn<<6],idx;
	void modif(int &nd,int l,int r,int p){
		if(!nd)nd=++idx,tag[nd]=1,tree[nd]=1;
		if(l==r)return ;
		if(p<=mid)modif(ls,l,mid,p);
		else modif(rs,mid+1,r,p);
	}
	void upd(int nd,int w){tree[nd]=tree[nd]*w%mod,tag[nd]=tag[nd]*w%mod;}
	void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=1;}
	int merge(int u,int v,int l,int r,int w1,int w2){
		if(!u){upd(v,w2);return v;}
		if(!v){upd(u,w1);return u;}
		if(l==r){
			tree[u]=(tree[u]*w1+tree[v]*w2+tree[u]*tree[v])%mod;
			return u;
		}
		if(tag[u]!=1)down(u);if(tag[v]!=1)down(v);
		int nd=++idx;tag[nd]=1;
		ls=merge(lc[u],lc[v],l,mid,w1,w2);
		rs=merge(rc[u],rc[v],mid+1,r,w1,w2);
		tree[nd]=(tree[ls]+tree[rs])%mod;
		return nd;
	}
	int query(int nd,int l,int r,int p){
		if(l==r)return tree[nd];
		if(tag[nd]!=1)down(nd);
		if(p<=mid)return query(ls,l,mid,p);
		else return query(rs,mid+1,r,p);
	}
}
int g[maxn];
ull lsh[maxn];int len;
void dfs(int nd,int l,int r){
	if(l+1==r){
		g[nd]=1;
		sgt::modif(rt[nd],1,len,hsh[l]);
		return ;
	}
	dfs(ls,l,md[nd]),dfs(rs,md[nd],r);
	rt[nd]=sgt::merge(rt[ls],rt[rs],1,len,g[rs],g[ls]);
	g[nd]=(2*g[ls]*g[rs]+sgt::tree[rt[nd]])%mod;
}
void work(){
	n=read();m=read();
	dfs(0,n);
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		a[i]={l,r};
		ull v=rnd();
		hsh[l]^=v,hsh[r]^=v;
	}
	for(int i=1;i<=n;i++)hsh[i]^=hsh[i-1];
	for(int i=0;i<=n;i++)lsh[++len]=hsh[i];
	sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh;
	for(int i=0;i<=n;i++)hsh[i]=lower_bound(lsh+1,lsh+len+1,hsh[i])-lsh;
	dfs(1,0,n);
	printf("%lld\n",(g[1]+sgt::query(rt[1],1,len,1))%mod);
}

bool med;
int T;
signed main(){
	// freopen("count.in","r",stdin);
	// freopen("count.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}