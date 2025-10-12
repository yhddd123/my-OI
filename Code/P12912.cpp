// Problem: P12912 [POI 2020/2021 R2] 收拾背包 / Pakowanie plecaka
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12912
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-10-12 15:52:49
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
const int inf=1e18;
bool mbe;

int n,a[maxn];
int s[maxn],ans[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
pii mx[maxn<<2];int tag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){mx[nd]={a[l]-s[l+1],l};return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mx[nd]=max(mx[ls],mx[rs]);
}
void upd(int nd,int w){mx[nd].fi+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
	// cout<<nd<<" "<<l<<" "<<r<<" "<<mx[nd].fi<<" "<<mx[nd].se<<"\n";
}
void modif(int nd,int l,int r,int p){
	if(l==r){mx[nd]={-inf,l};return ;}
	if(tag[nd])down(nd);
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	mx[nd]=max(mx[ls],mx[rs]);
}
priority_queue<pii> q; 
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n;i;i--)s[i]=s[i+1]+a[i];
	build(1,1,n);
	ans[n]=s[1];
	for(int i=n-1;i;i--){
		pii p=mx[1];
		while(p.fi>0){
			q.push({a[p.se],p.se});
			modif(1,1,n,p.se);
			p=mx[1];
		}
		int pos=q.top().se;
		updata(1,1,n,1,pos-1,a[pos]);
		ans[i]=ans[i+1]-q.top().fi;q.pop();
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