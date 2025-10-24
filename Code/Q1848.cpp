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

int n,q,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2],mn[maxn<<2],tag[maxn<<2],cov[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){mn[nd]=mx[nd]=a[l];return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]);
}
void updt(int nd,int w){mn[nd]+=w,mx[nd]+=w,tag[nd]+=w;}
void updc(int nd,int w){mn[nd]=mx[nd]=w,tag[nd]=0,cov[nd]=w;}
void down(int nd){
	if(cov[nd])updc(ls,cov[nd]),updc(rs,cov[nd]),cov[nd]=0;
	if(tag[nd])updt(ls,tag[nd]),updt(rs,tag[nd]),tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		if(mx[nd]==w&&mn[nd]>=w-1)return updt(nd,1);
		if(mx[nd]<w)return updc(nd,w);
	}
	down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mx[nd];
	down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void down(int nd,int l,int r){
	if(l==r){a[l]=mx[nd];return ;}
	down(nd);
	down(ls,l,mid),down(rs,mid+1,r);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	while(q--){
		int l=read(),r=read(),mx=query(1,1,n,l,r);
		updata(1,1,n,l,r,mx);
	// down(1,1,n);
	// for(int i=1;i<=n;i++)printf("%lld ",a[i]);puts("");
	}
	down(1,1,n);
	for(int i=1;i<=n;i++)printf("%lld ",a[i]);
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