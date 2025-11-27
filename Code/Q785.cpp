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

int n,q,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2],mn[maxn<<2],his[maxn<<2];
int tag[maxn<<2],htag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){mx[nd]=mn[nd]=his[nd]=a[l];return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mx[nd]=max(mx[ls],mx[rs]),mn[nd]=min(mn[ls],mn[rs]),his[nd]=max(his[ls],his[rs]);
}
void upd(int nd,int w,int hw){
	his[nd]=max(his[nd],mx[nd]+hw),htag[nd]=max(htag[nd],tag[nd]+hw);
	mn[nd]+=w,mx[nd]+=w,tag[nd]+=w;
}
void down(int nd){upd(ls,tag[nd],htag[nd]),upd(rs,tag[nd],htag[nd]),tag[nd]=htag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w,w);
	down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]),mn[nd]=min(mn[ls],mn[rs]),his[nd]=max(his[ls],his[rs]);
}
void modif(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		if(mn[nd]==mx[nd])return upd(nd,w-mx[nd],w-mx[nd]);
	}
	down(nd);
	if(ql<=mid)modif(ls,l,mid,ql,qr,w);
	if(qr>mid)modif(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]),mn[nd]=min(mn[ls],mn[rs]),his[nd]=max(his[ls],his[rs]);
}
int quemx(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mx[nd];
	down(nd);
	if(qr<=mid)return quemx(ls,l,mid,ql,qr);
	if(ql>mid)return quemx(rs,mid+1,r,ql,qr);
	return max(quemx(ls,l,mid,ql,qr),quemx(rs,mid+1,r,ql,qr));
}
int quehis(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return his[nd];
	down(nd);
	if(qr<=mid)return quehis(ls,l,mid,ql,qr);
	if(ql>mid)return quehis(rs,mid+1,r,ql,qr);
	return max(quehis(ls,l,mid,ql,qr),quehis(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	while(q--){
		int op=read();
		if(op==1){
			int l=read(),r=read(),w=read();
			updata(1,1,n,l,r,w);
		}
		if(op==2){
			int l=read(),r=read(),w=read();
			modif(1,1,n,l,r,w);
		}
		if(op==3){
			int l=read(),r=read();
			printf("%lld\n",quemx(1,1,n,l,r));
		}
		if(op==4){
			int l=read(),r=read();
			printf("%lld\n",quehis(1,1,n,l,r));
		}
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