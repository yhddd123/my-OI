// Problem: CF1515I Phoenix and Diamonds
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1515I
// Memory Limit: 1000 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-06-05 12:50:24
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline ll read(){
	ll x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const ll inf=1e18;
bool mbe;

int n,q;
ll a[maxn];int w[maxn],v[maxn];
int id[maxn],rnk[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
ll lim[maxn<<2][17],sum[maxn<<2][17],res[maxn<<2][17];
void init(int nd,int p){
	for(int i=0;i<=16;i++){
		sum[nd][i]=res[nd][i]=0,lim[nd][i]=inf;
		if(w[p]<(1<<i+1))sum[nd][i]=1ll*w[p]*a[p],res[nd][i]=1ll*v[p]*a[p];
		if(a[p]&&w[p]<(1<<i+1)&&(1<<i)<=w[p])lim[nd][i]=w[p];
	}
}
void up(int nd){
	for(int i=0;i<=16;i++){
		sum[nd][i]=sum[ls][i]+sum[rs][i];
		res[nd][i]=res[ls][i]+res[rs][i];
		lim[nd][i]=min(lim[ls][i],(i?sum[ls][i-1]:0)+lim[rs][i]);
	}
}
void build(int nd,int l,int r){
	if(l==r)return init(nd,id[l]);
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd);
}
void modif(int nd,int l,int r,int p){
	if(l==r)return init(nd,id[l]);
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	up(nd);
}
ll val,k;
ll query(int nd,int l,int r){
	if(!val)return 0;
	if(l==r){
		int num=min(a[id[l]],val/w[id[l]]);
		val-=1ll*num*w[id[l]];
		return 1ll*num*v[id[l]];
	}
	while((1<<k)>val)k--;
	// cout<<val<<" "<<k<<"\n";
	if(sum[nd][k]<=val){val-=sum[nd][k];return res[nd][k];}
	if(k&&sum[nd][k-1]<=val&&val<lim[nd][k]){val-=sum[nd][k-1];return res[nd][k-1];}
	// cout<<l<<" "<<r<<" "<<val<<" "<<k<<"\n";
	return query(ls,l,mid)+query(rs,mid+1,r);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),w[i]=read(),v[i]=read(),id[i]=i;
	sort(id+1,id+n+1,[&](int x,int y){return v[x]>v[y]||(v[x]==v[y]&&w[x]<w[y]);});
	for(int i=1;i<=n;i++)rnk[id[i]]=i;
	// for(int i=1;i<=n;i++)cout<<id[i]<<" ";cout<<"\n";
	build(1,1,n);
	while(q--){
		int op=read();
		if(op==1){
			int k=read(),p=read();
			a[p]+=k;
			modif(1,1,n,rnk[p]);
		}
		if(op==2){
			int k=read(),p=read();
			a[p]-=k;
			modif(1,1,n,rnk[p]);
		}
		if(op==3){
			val=read();
			k=16;while(k&&(1<<k)>val)k--;
			printf("%lld\n",query(1,1,n));
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