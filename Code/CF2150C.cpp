// Problem: C. Limited Edition Shop
// Contest: Codeforces - Codeforces Round 1053 (Div. 1)
// URL: https://codeforces.com/contest/2150/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-09-24 19:52:35
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn],v[maxn];
int pa[maxn],pb[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
    mx[nd]=tag[nd]=0;
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,int w){mx[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(ql>qr)return ;
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    mx[nd]=max(mx[ls],mx[rs]);
}
void modif(int nd,int l,int r,int p,int w){
    if(l==r){mx[nd]=w;return ;}
    if(tag[nd])down(nd);
    if(p<=mid)modif(ls,l,mid,p,w);
    else modif(rs,mid+1,r,p,w);
    mx[nd]=max(mx[ls],mx[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mx[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)v[i]=read();v[n+1]=0;
	for(int i=1;i<=n;i++)a[i]=read();a[n+1]=n+1;
	for(int i=1;i<=n;i++)b[i]=read();b[n+1]=n+1;
	for(int i=1;i<=n+1;i++)pa[a[i]]=i,pb[b[i]]=i;
	build(1,0,n+1);
	for(int i=1;i<=n+1;i++){
		int id=a[i];
		modif(1,0,n+1,pb[id],query(1,0,n+1,0,pb[id]));
		updata(1,0,n+1,0,pb[id]-1,v[id]);
		// for(int j=0;j<=n+1;j++)cout<<query(1,0,n+1,j,j)<<" ";cout<<"\n";
	}
	printf("%lld\n",mx[1]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}