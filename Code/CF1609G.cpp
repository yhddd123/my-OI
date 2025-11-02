// Problem: CF1609G A Stroll Around the Matrix
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1609G
// Memory Limit: 250 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2025-11-01 10:33:12
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
const int maxn=110;
const int maxm=100010;
const int inf=1e9;
bool mbe;

int n,m,q;
int a[maxn],b[maxm];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxm<<2],sum[maxm<<2],len[maxm<<2],val[maxm<<2],cnt[maxm<<2],tag[maxm<<2];
void up(int nd){
	mn[nd]=min(mn[ls],mn[rs]);
	sum[nd]=sum[ls]+sum[rs];
	val[nd]=val[ls]+val[rs];
}
void build(int nd,int l,int r){
	len[nd]=r-l+1,cnt[nd]=(l+r)*(r-l+1)/2;
	if(l==r){
		mn[nd]=sum[nd]=b[l];val[nd]=b[l]*l;
		return ;
	}
	build(ls,l,mid);build(rs,mid+1,r);
	up(nd);
}
void upd(int nd,int w){mn[nd]+=w,sum[nd]+=len[nd]*w,val[nd]+=cnt[nd]*w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]);upd(rs,tag[nd]);tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){upd(nd,w);return ;}
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	up(nd);
}
int query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return 0;
	if(l>=ql&&r<=qr)return sum[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int findr(int nd,int l,int r,int w){
	if(mn[nd]>=w)return 1;
	if(l==r)return l;
	if(tag[nd])down(nd);
	if(mn[rs]<w)return findr(rs,mid+1,r,w);
	else return findr(ls,l,mid,w);
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	for(int i=n;i;i--)a[i]-=a[i-1];
	for(int i=m;i;i--)b[i]-=b[i-1];
	build(1,2,m);
	while(q--){
		int op=read(),k=read(),d=read();
		if(op==1){
			for(int i=n-k+1;i<=n;i++)a[i]+=d;
		}
		else{
			if(k==m)b[1]+=d,k--;
			updata(1,2,m,m-k+1,m,d);
			// for(int i=m-k+1;i<=m;i++)b[i]+=d;
		}
		// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
		// for(int i=1;i<=m;i++)cout<<b[i]<<" ";cout<<"\n";
		// cout<<mn[1]<<"\n";
		int ans=(a[1]+b[1])*(n+m-1);
		for(int i=2;i<=n;i++){
			int p=findr(1,2,m,a[i]);
			// cout<<i<<" "<<p<<"\n";
			ans+=a[i]*(n+m-(i-1+p-1)-1);
			ans-=query(1,2,m,p+1,m);
		}
		ans+=sum[1]*(n+m);ans-=val[1];
		// for(int i=2;i<=n;i++){
			// int p=upper_bound(b+2,b+m+1,a[i])-b-1;
			// ans+=a[i]*(n+m-(i-1+p-1)-1);
			// for(int j=p+1;j<=m;j++)ans-=b[j];
			// cout<<i<<" "<<p<<"\n";
		// }
		// for(int i=2;i<=m;i++)ans+=b[i]*(n+m-i);
		printf("%lld\n",ans);
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