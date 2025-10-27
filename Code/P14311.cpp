// Problem: P14311 【MX-S8-T4】平衡三元组
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14311
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-10-27 17:07:08
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
const int maxn=1000010;
const int inf=1e18;
bool mbe;

int n,q,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
pii mx[maxn<<2];int tag[maxn<<2];
void build(int nd,int l,int r){
    if(l==r){mx[nd]={a[l],l};return ;}
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
}
pii query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mx[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	while(q--){
		int op=read();
		if(op==1){
			int l=read(),r=read(),ans=-inf;
			auto[ap,p]=query(1,1,n,l,r);
			// cout<<l<<" "<<p<<" "<<r<<"\n";
			if(p+1<r){
				auto[ax,x]=query(1,1,n,p+1,r);
				if(p+1<x)ans=max(ans,ap+ax+query(1,1,n,p+1,x-1).fi);
				while(x<r){
					auto[ay,y]=query(1,1,n,x+1,r);
					if(ap+ay>=2*ax){ans=max(ans,ap+ax+ay);break;}
					if(x+1<y)ans=max(ans,ap+ay+query(1,1,n,x+1,y-1).fi);
					x=y,ax=ay;
				}
			}
			if(l<p-1){
				auto[ax,x]=query(1,1,n,l,p-1);
				if(x<p-1)ans=max(ans,ap+ax+query(1,1,n,x+1,p-1).fi);
				while(l<x){
					auto[ay,y]=query(1,1,n,l,x-1);
					if(ap+ay>=2*ax){ans=max(ans,ap+ax+ay);break;}
					if(y+1<x)ans=max(ans,ap+ay+query(1,1,n,y+1,x-1).fi);
					x=y,ax=ay;
				}
			}
			if(ans==-inf)puts("No");
			else printf("%lld\n",ans);
		}
		else{
			int l=read(),r=read(),x=read();
			updata(1,1,n,l,r,x);
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