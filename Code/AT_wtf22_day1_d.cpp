// Problem: AT_wtf22_day1_d Welcome to Tokyo!
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_wtf22_day1_d
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-01-28 09:47:25
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
const int inf=1e9;
bool mbe;

int n,m;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
pii mx[maxn<<2];int tag[maxn<<2];
pii mn[maxn<<2];
multiset<int> val[maxn];
void build(int nd,int l,int r){
	mx[nd]={0,r};
	mn[nd]={n+1,l};
	if(l==r){
		val[l].insert(n+1);
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
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
void modif(int nd,int l,int r,int p,int w){
	if(l==r){
		if(w>0)val[l].insert(w),mn[nd]=min(mn[nd],{w,l});
		else val[l].erase(val[l].find(-w)),mn[nd]={*val[l].begin(),l};
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	mn[nd]=min(mn[ls],mn[rs]);
}
pii query(int nd,int l,int r,int p){
	if(l>=p)return mn[nd];
	if(p>mid)return query(rs,mid+1,r,p);
	return min(query(ls,l,mid,p),query(rs,mid+1,r,p));
}
int f[maxn],ans[maxn];
void work(){
	n=read();m=read();
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		modif(1,1,n,l,r);
	}
	for(int i=1;i<=m;i++){
		f[i]=f[i-1];
		while(1){
			pii p=mx[1];
			int fr=1;if(p.fi==i)fr=p.se+1;
			if(fr>n)break;
			auto[r,l]=query(1,1,n,fr);
			if(r==n+1)break;
			f[i]++;
			updata(1,1,n,l,r,1);
			modif(1,1,n,l,-r);
		}
	}
	for(int i=1,j=m;i<=n;i++){
		while(j&&m-f[j-1]+(j-1)*i<=m-f[j]+j*i)j--;
		ans[i]=m-f[j]+j*i;
		// for(int j=0;j<=m;j++)ans[i]=min(ans[i],m-f[j]+j*i);
		printf("%lld\n",ans[i]);
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