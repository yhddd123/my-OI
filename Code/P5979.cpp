// Problem: P5979 [PA 2014] Druzyny
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5979
// Memory Limit: 256 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2025-04-09 18:02:32
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n;
pii a[maxn];
pii merge(pii u,pii v){return {max(u.fi,v.fi),min(u.se,v.se)};}
pii dp[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
pii operator+(pii u,pii v){
	pii res;
	res.fi=max(u.fi,v.fi),inc(res.se=(u.fi==res.fi)*u.se,(v.fi==res.fi)*v.se);
	return res;
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
pii tree[maxn<<2];
void build(int nd,int l,int r){
	tree[nd]={-inf,0};
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int p,pii w){
	if(l==r){tree[nd]=w;return ;}
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
pii query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return {-inf,0};
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
vector<pii> que[maxn];
void sovle(int l,int r){
	if(l>=r)return;
	sovle(l,mid);
	for(int i=mid+1;i<=r+1;i++)que[i].clear();
	pii tmp={1,n};
	for(int i=mid;i>=l;i--){
		if(tmp.fi>tmp.se||i+tmp.se<=mid)break;
		if(i+tmp.fi<=r){
			que[max(mid+1,i+tmp.fi)].pb({i,1});
			que[min(r+1,i+tmp.se+1)].pb({i,0});
		}
		tmp=merge(tmp,a[i]);
	}
	tmp={1,n};
	for(int i=mid+1;i<=r;i++){
		tmp=merge(tmp,a[i]);
		for(auto[j,op]:que[i]){
			if(op)updata(1,0,n,j,dp[j]);
			else updata(1,0,n,j,{-inf,0});
		}
		if(tmp.fi>tmp.se||mid+tmp.se<i)break;
		pii res=query(1,0,n,max(l,i-tmp.se),min(i-tmp.fi,mid));
		res.fi++;
		dp[i]=dp[i]+res;
	}
	for(int i=l;i<=mid;i++)updata(1,0,n,i,{-inf,0});
	sovle(mid+1,r);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	build(1,0,n);
	for(int i=1;i<=n;i++)dp[i]={-inf,0};dp[0]={0,1};
	sovle(0,n);
	if(dp[n].fi<=0)puts("NIE");
	else printf("%lld %lld\n",dp[n].fi,dp[n].se);
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