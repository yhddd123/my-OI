// Problem: CF679E Bear and Bad Powers of 42
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF679E
// Memory Limit: 250 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-06-02 15:46:10
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
int pw[10],p[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2],t1[maxn<<2],t2[maxn<<2],t3[maxn<<2];
void mdf(int nd,int w1,int w2){
	mn[nd]=t1[nd]=w1,t2[nd]=w2,t3[nd]=0;
}
void upd(int nd,int w){
	if(t2[nd]){
		t1[nd]-=w;
		while(t1[nd]<0)t1[nd]+=pw[t2[nd]+1]-pw[t2[nd]],t2[nd]++;
		mn[nd]=t1[nd];
	}
	else mn[nd]-=w,t3[nd]+=w;
}
void down(int nd){
	if(t1[nd])mdf(ls,t1[nd],t2[nd]),mdf(rs,t1[nd],t2[nd]),t1[nd]=t2[nd]=0;
	if(t3[nd])upd(ls,t3[nd]),upd(rs,t3[nd]),t3[nd]=0;
}
void modif(int nd,int l,int r,int ql,int qr,int w1,int w2){
	if(l>=ql&&r<=qr)return mdf(nd,w1,w2);
	down(nd);
	if(ql<=mid)modif(ls,l,mid,ql,qr,w1,w2);
	if(qr>mid)modif(rs,mid+1,r,ql,qr,w1,w2);
	mn[nd]=min(mn[ls],mn[rs]);
}
bool updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr&&(t2[nd]||mn[nd]>=w))return upd(nd,w),mn[nd]==0;
	down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]);
	return mn[nd]==0;
}
int query(int nd,int l,int r,int p){
	if(l==r)return pw[t2[nd]]-t1[nd];
	down(nd);
	if(p<=mid)return query(ls,l,mid,p);
	else return query(rs,mid+1,r,p);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	pw[0]=1;for(int i=1;i<10;i++)pw[i]=pw[i-1]*42;
	for(int i=1;i<=n;i++)modif(1,1,n,i,i,(*lower_bound(pw,pw+10,a[i]))-a[i],lower_bound(pw,pw+10,a[i])-pw);
	while(q--){
		int op=read();
		if(op==1)printf("%lld\n",query(1,1,n,read()));
		if(op==2){
			int l=read(),r=read(),x=read();
			modif(1,1,n,l,r,(*lower_bound(pw,pw+10,x))-x,lower_bound(pw,pw+10,x)-pw);
		}
		if(op==3){
			int l=read(),r=read(),x=read();
			while(updata(1,1,n,l,r,x));
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