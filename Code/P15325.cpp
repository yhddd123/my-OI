// Problem: P15325 【MX-X24-T6】「RiOI-7」Stardust:RAY
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P15325
// Memory Limit: 2048 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-23 15:36:27
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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
#define put() putchar(' ')
#define endl puts("")
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n,q,qq,a[maxn],b[maxn];
int tim[maxn];
vector<tuple<int,int,int>> upd[maxn],que[maxn];
int ans[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
namespace sgt1{
	int mn[maxn<<2],mx[maxn<<2];
	void build(int nd,int l,int r){
		if(l==r){
			mn[nd]=mx[nd]=b[l];
			return ;
		}
		build(ls,l,mid),build(rs,mid+1);
		mn[nd]=min(mn[ls],mn[rs]);
		mx[nd]=max(mx[ls],mx[rs]);
	}
	void modif(int nd,int l,int r,int p){
		if(l==r){
			mn[nd]=mx[nd]=b[l];
			return ;
		}
		if(p<=mid)modif(ls,l,mid,p);
		else modif(rs,mid+1,r,p);
		mn[nd]=min(mn[ls],mn[rs]);
		mx[nd]=max(mx[ls],mx[rs]);
	}
	int findl(int nd,int l,int r,int w){
		if(l==r)return l;
		if(mn[ls]<w)return findl(ls,l,mid,w);
		else return findl(rs,mid+1,r,mid,w);
	}
	int findr(int nd,int l,int r,int w){
		if(l==r)return l;
		if(mx[ls]>w)return findr(ls,l,mid,w);
		else return findr(rs,mid+1,r,w);
	}
}
pii operator*(pii u,int v){return {u.fi*v,u.se*v};}
pii operator+(pii u,pii v){return {u.fi+v.fi,u.se+v.se};}
struct node{
	int x,y;pii v1,v2,v3;
};
void upd(node &u,node v){
	if(u.x==v.x)u.v1=u.v1+v.v1;
	if(u.y==v.y)u.v2=u.v2+v.v2;
	if(u.x==v.x&&u.y==v.y)u.v3=u.v3+v.v3;
	else if(u.x==v.x)u.v3=u.v3+v.v1*u.y;
	else u.v3=u.v3+v.v2*u.x;
}
namespace sgt2{
	int mx[maxn<<2],smx[maxn<<2],mn[maxn<<2],smn[maxn<<2];
	void up(int nd){
		mx[nd]=max(mx[ls],mx[rs]);
		smx[nd]=max(mx[ls]==mx[nd]?smx[ls]:mx[ls],mx[rs]==mx[nd]?smx[rs]:mx[rs]);
		mn[nd]=min(mn[ls],mn[rs]);
		smn[nd]=min(mn[ls]==mn[nd]?smn[ls]:mn[ls],mn[rs]==mn[nd]?smn[rs]:mn[rs]);
	}
	void build(int nd,int l,int r){
		mx[nd]=smx[nd]=n+1,mn[nd]=smn[nd]=0;
		if(l==r)return ;
		up(nd);
	}
	int tagx[maxn<<2],tagy[maxn<<2];
	void updx(int nd,int w){}
	void updmn(int nd,int l,int r,int ql,int qr,int w,int t){
		if(w>=mx[nd])return ;
		if(l>=ql&&r<=qr){
			if(mx[nd]==smx[nd])updx(nd,w-mx[nd]);
		}
		down(nd);
		if(ql<=mid)updmn(ls,l,mid,ql,qr,w);
		if(qr>mid)updmn(rs,mid+1,r,ql,qr,w);
		up(nd);
	}
	void updmx(int nd,int l,int r,int ql,int qr,int w){
		if(w<=mn[nd])return ;
		if(l>=ql&&r<=qr){
			if(mn[nd]==smn[nd])updy(nd,w);
		}
		down(nd);
		if(ql<=mid)updmx(ls,l,mid,ql,qr,w);
		if(qr>mid)updmx(rs,mid+1,r,ql,qr,w);
		up(nd);
	}
	node query(int nd,int l,int r,int p){
		if(l==r)return tree[nd];
		down(nd);
		if(p<=mid)return query(ls,l,mid,p);
		else return query(rs,mid+1,r,p);
	}
	
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read()+1,b[a[i]]=i;
	sgt1::build(1,1,n);
	for(int t=1;t<=q;t++){
		int o=read(),l=read(),r=read();
		if(o==1){
			if(tim[a[l]]<qq)upd[a[l]].pb({b[a[l]],tim[i]+1,qq}),tim[a[l]]=qq;
			if(tim[a[r]]<qq)upd[a[r]].pb({b[a[r]],tim[i]+1,qq}),tim[a[r]]=qq;
			swap(a[l],a[r]),swap(b[a[l]],b[a[r]]);
			sgt1::modif(1,1,n,a[l]);
			sgt1::modif(1,1,n,a[r]);
		}
		else{
			++qq;
			int k=min(findl(1,1,n,l),findr(1,1,n,r))-1;
			if(l==1&&r==n)k=n;
			que[k].pb({qq,l,r});
		}
	}
	for(int i=1;i<=n;i++)if(tim[i]<qq)upd[i].pb({b[i],tim[i]+1,qq});
	sgt2::build(1,1,qq);
	for(int i=1;i<=n;i++){
		for(auto[v,l,r]:upd[i])sgt2::updmn(1,1,qq,l,r,v,i),sgt2::updmx(1,1,n,l,r,v,i);
		for(auto[t,l,r]:que[i]){
			auto[x,y,v1,v2,v3]=sgt2::query(1,1,qq,t);
			ans[t]=(r+1)*(v1.fi*i+v1.se)+(l+1)*(v2.fi*i+v2.se)-(v3.fi*i+v3.se)-(l-1)*(r+1);
		}
	}
	for(int i=1;i<=qq;i++)printf("%lld\n",ans[t]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}