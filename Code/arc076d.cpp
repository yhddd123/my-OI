// Problem: AT_arc076_d [ARC076F] Exhausted?
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc076_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-04-16 18:13:27
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,ans;
vector<int> que[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
#define all 1,1,m+1
int mx[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){mx[nd]=-(m-l+1);return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mx[nd]=max(mx[ls],mx[rs]);
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
int query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return 0;
	if(l>=ql&&r<=qr)return mx[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();m=read();ans=n-m;
	build(all);
	int res=0;
	for(int i=1;i<=n;i++){
		int l=read(),r=read();
		que[l].pb(r);
	}
	for(int i=0;i<=m;i++){
		for(int r:que[i])updata(all,i+1,r,1);
		ans=max(ans,query(all,i+1,m+1));
		upd(1,-1);
	}
	printf("%lld\n",ans);
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