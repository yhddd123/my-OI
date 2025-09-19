// Problem: P9000 [CEOI 2022] Measures
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9000
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2025-09-19 19:06:57
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
const int maxn=200100;
const int inf=1e18;
bool mbe;

int n,m,d,a[maxn];
int id[maxn],rnk[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct nd{
	int mx,mn,ans;
}tree[maxn<<2];
int tag[maxn<<2];
nd merge(nd u,nd v){return {max(u.mx,v.mx),min(u.mn,v.mn),max({u.ans,v.ans,u.mx-v.mn})};}
void build(int nd,int l,int r){
	if(l==r){tree[nd]={-inf,inf,0};return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	tree[nd]=merge(tree[ls],tree[rs]);
}
void upd(int nd,int w){tree[nd].mx+=w,tree[nd].mn+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=merge(tree[ls],tree[rs]);
}
void modif(int nd,int l,int r,int p,int w){
	if(l==r){tree[nd]={w,w,0};return ;}
	if(tag[nd])down(nd);
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	tree[nd]=merge(tree[ls],tree[rs]);
}
#define lb(x) (x&(-x))
int sum[maxn];
void upd(int x){while(x<=n+m)sum[x]++,x+=lb(x);}
int que(int x){int res=0;while(x)res+=sum[x],x-=lb(x);return res;}
void mdf(int i){
	int cnt=que(rnk[i]);upd(rnk[i]);
	modif(1,1,n+m,rnk[i],a[i]-d*cnt);
	// cout<<i<<" "<<cnt<<"\n";
	updata(1,1,n+m,rnk[i],n+m,-d);
	// for(int i=1;i<=5;i++)down(i),cout<<tree[i].mx<<" "<<tree[i].mn<<" "<<tree[i].ans<<"\n";
}
void work(){
	n=read();m=read();d=read();
	build(1,1,n+m);
	for(int i=1;i<=n+m;i++)a[i]=read(),id[i]=i;
	sort(id+1,id+n+m+1,[&](int u,int v){return a[u]<a[v];});
	for(int i=1;i<=n+m;i++)rnk[id[i]]=i;
	for(int i=1;i<=n;i++)mdf(i);
	for(int i=1;i<=m;i++){
		mdf(i+n);
		int res=tree[1].ans;
		if(res&1)printf("%lld.5 ",res/2);
		else printf("%lld ",res/2);
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