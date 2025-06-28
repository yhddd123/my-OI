// Problem: P5324 [BJOI2019] 删数
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5324
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-03-11 12:39:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=150010;
const int maxm=450010;
const int inf=2e9;
bool mbe;

int n,q,a[maxn],ans;
int c[maxm],p;
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
#define all 1,1,maxm
pii tree[maxm<<2];
pii operator*(pii u,pii v){return {min(u.fi,v.fi),(u.fi<=v.fi)*u.se+(v.fi<=u.fi)*v.se};}
int tag[maxm<<2];
void build(int nd,int l,int r){
	tree[nd]={0,r-l+1};
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,int w){tree[nd].fi+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void modif(int nd,int l,int r,int p,int w){
	if(l==r){
		tree[nd].fi+=w;
		return ;
	}
	if(tag[nd])down(nd);
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]*tree[rs];
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]*tree[rs];
}
pii query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)*query(rs,mid+1,r,ql,qr);
}
void add(int x){
	if(x<=p+n)modif(all,x-c[x],1);
	c[x]++;
}
void del(int x){
	c[x]--;
	if(x<=p+n)modif(all,x-c[x],-1);
}
void work(){
	n=read();q=read();p=maxn;
	build(all);
	for(int i=1;i<=n;i++)a[i]=read()+p,add(a[i]);
	// pii res=query(all,p+1,p+n);
	// cout<<res.fi<<" "<<res.se<<"\n";
	while(q--){
		int u=read(),v=read();
		if(!u){
			if(v==1){
				updata(all,p+n-c[p+n]+1,p+n,-1);
				p--;
			}
			else{
				p++;
				updata(all,p+n-c[p+n]+1,p+n,1);
			}
		}
		else{
			v+=p;
			del(a[u]);
			// cout<<u<<" "<<a[u]<<" "<<v<<"\n";
			a[u]=v;
			add(a[u]);
		}
		pii res=query(all,p+1,p+n);
		// cout<<res.fi<<" "<<res.se<<"\n";
		printf("%lld\n",res.fi==0?res.se:0);
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