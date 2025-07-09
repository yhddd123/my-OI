// Problem: P10560 [ICPC 2024 Xi'an I] Holes and Balls
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10560
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-05-30 08:08:11
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int lim[maxn],siz[maxn],fa[maxn];
void dfs(int u,int fa){
	::fa[u]=fa;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];
	}
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
pii tree[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){tree[nd]={a[l],l};return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	tree[nd]=min(tree[ls],tree[rs]);
}
void modif(int nd,int l,int r,int p){
	if(l==r){tree[nd]={inf,p};return ;}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	tree[nd]=min(tree[ls],tree[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
int mn[maxn<<2],tag[maxn<<2],pl[maxn<<2],pr[maxn<<2],pos[maxn];
void init(int nd,int l,int r){
	pl[nd]=l,pr[nd]=r;
	if(l==r){mn[nd]=n-l+1;pos[l]=nd;return ;}
	init(ls,l,mid),init(rs,mid+1,r);
	mn[nd]=min(mn[ls],mn[rs]);
}
void upd(int nd,int w){mn[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]);
}
void down(int nd,int l,int r,int p){
	if(l==r)return ;
	if(tag[nd])down(nd);
	if(p<=mid)down(ls,l,mid,p);
	else down(rs,mid+1,r,p);
}
int find(int p,int w){
	int nd=pos[p];down(1,1,n,p);
	if(mn[nd]<w)return p-1;
	while(nd!=1){
		int lst=nd;
		nd=nd>>1;
		if(lst==ls){
			if(mn[rs]<w){nd=rs;break;}
		}
	}
	if(nd==1)return n;
	int l=pl[nd],r=pr[nd];
	while(l<r){
		if(tag[nd])down(nd);
		if(mn[ls]<w)nd=ls,r=mid;
		else nd=rs,l=mid+1;
	}
	return l-1;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	build(1,1,n),init(1,1,n);
	for(int i=1;i<=n;i++){
		lim[i]=lim[fa[i]];
		int p=find(lim[i]+1,siz[i]);
		// cout<<i<<" "<<lim[i]+1<<" "<<p<<endl;
		pii res=query(1,1,n,lim[i]+1,p);
		modif(1,1,n,res.se);
		updata(1,1,n,lim[i]+1,res.se,-siz[i]);
		ans[i]=res.fi;lim[i]=res.se;
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
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