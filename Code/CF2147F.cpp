// Problem: F. Exchange Queries
// Contest: Codeforces - Codeforces Global Round 29 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2147/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-09-22 10:42:48
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
int id[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int pl,pr,ans;
}sum[maxn<<2],val[maxn<<2];
node operator +(node u,node v){
	if(!u.ans)return v;
	if(!v.ans)return u;
	return {u.pl,v.pr,u.ans+v.ans-v.pl*u.pr};
}
int mx[maxn<<2];
node query(int nd,int l,int r,int w){
	if(w<l)return sum[nd];
	if(w>r)return {0,0,0};
	if(l==r){
		if(max(mx[nd],w)<=l)return {l,l,l*l};
		return {0,0,0};
	}
	if(w<=mid)return query(ls,l,mid,w)+val[rs];
	return query(rs,mid+1,r,max(w,mx[ls]));
}
void up(int nd,int l,int r){
	mx[nd]=max(mx[ls],mx[rs]);
	val[rs]=query(rs,mid+1,r,mx[ls]);
	sum[nd]=sum[ls]+val[rs];
}
void build(int nd,int l,int r){
	if(l==r){
		mx[nd]=a[l];
		if(mx[nd]<=l)sum[nd]={l,l,l*l};
		else sum[nd]={0,0,0};
		return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd,l,r);
	// cout<<nd<<" "<<l<<" "<<r<<" "<<sum[nd].pl<<" "<<sum[nd].pr<<" "<<sum[nd].ans<<"\n";
}
void modif(int nd,int l,int r,int p){
	if(l==r){
		mx[nd]=a[l];
		if(mx[nd]<=l)sum[nd]={l,l,l*l};
		else sum[nd]={0,0,0};
		return ;}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	up(nd,l,r);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)id[i]=read();
	for(int i=1;i<=n;i++)a[id[i]]=read();
	build(1,1,n);
	while(q--){
		int op=read(),u=read(),v=read();
		if(op==1)swap(id[u],id[v]),swap(a[id[u]],a[id[v]]);
		else swap(a[id[u]],a[id[v]]);
		modif(1,1,n,id[u]),modif(1,1,n,id[v]);
		// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
		// cout<<sum[1].ans<<"\n";
		printf("%lld\n",sum[1].ans);
	}
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