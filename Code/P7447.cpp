// Problem: P7447 [Ynoi2007] rgxsxrs
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7447
// Memory Limit: 64 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-06-13 15:00:21
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod (1<<20)-1
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;
const int inf=2e9;
const int B=32;
const int D=64,M=5,pw[]={1,64,4096,262144,16777216};
bool mbe;

inline void chkmin(int &x,const int &y){x=x<y?x:y;}
inline void chkmax(int &x,const int &y){x=x>y?x:y;}

int n,q,ans;
int a[maxn],b[maxn];
int num,pl[maxn],pr[maxn],bel[maxn];
inline int calc(int v){return upper_bound(pw,pw+M,v)-pw-1;}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int l,r;
	int mn[M],mx[M],tag[M],cnt[M];
	ll sum[M];
}tree[32768];
inline void blk_up(node &u,int k){
	u.mn[k]=inf,u.mx[k]=u.tag[k]=u.cnt[k]=u.sum[k]=0;
	for(int i=u.l;i<=u.r;i++)if(b[i]==k){
		chkmin(u.mn[k],a[i]);
		chkmax(u.mx[k],a[i]);
		u.cnt[k]++;u.sum[k]+=a[i];
	}
}
inline void blk_up(node &u){
	for(int i=0;i<M;i++)u.mn[i]=inf,u.mx[i]=u.tag[i]=u.cnt[i]=u.sum[i]=0;
	for(int i=u.l;i<=u.r;i++){
		chkmin(u.mn[b[i]],a[i]);
		chkmax(u.mx[b[i]],a[i]);
		u.cnt[b[i]]++;u.sum[b[i]]+=a[i];
	}
}
inline void up(int nd,int k){
	chkmin(tree[nd].mn[k]=tree[ls].mn[k],tree[rs].mn[k]);
	chkmax(tree[nd].mx[k]=tree[ls].mx[k],tree[rs].mx[k]);
	tree[nd].cnt[k]=tree[ls].cnt[k]+tree[rs].cnt[k];
	tree[nd].sum[k]=tree[ls].sum[k]+tree[rs].sum[k];
}
inline void up(int nd){
	for(int i=0;i<M;i++)up(nd,i);
}
inline void build(int nd,int l,int r){
	if(l==r)return tree[nd].l=pl[l],tree[nd].r=pr[l],blk_up(tree[nd]);
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd);
}
inline void upd(node &u,int k,int w){
	if(!u.cnt[k])return ;
	u.mn[k]-=w,u.mx[k]-=w,u.tag[k]+=w,u.sum[k]-=1ll*w*u.cnt[k];
}
inline void down(int nd,int k){
	if(!tree[nd].tag[k])return ;
	upd(tree[ls],k,tree[nd].tag[k]),upd(tree[rs],k,tree[nd].tag[k]),tree[nd].tag[k]=0;
}
inline void down(int nd){
	for(int i=0;i<M;i++)down(nd,i);
}
inline void blk_down(node &u,int k){
	if(!u.tag[k])return ;
	for(int i=u.l;i<=u.r;i++)if(b[i]==k)a[i]-=u.tag[k];
	u.tag[k]=0;
}
inline void blk_down(node &u){
	for(int i=u.l;i<=u.r;i++)a[i]-=u.tag[b[i]];
	for(int i=0;i<M;i++)u.tag[i]=0;
}
int ql,qr,idl,idr;
inline void leaf_down(int nd,int k){
	for(int i=__lg(nd);i;i--)down(nd>>i,k);
	blk_down(tree[nd],k);
}
inline void leaf_up(int nd,int k){
	blk_up(tree[nd],k);
	nd>>=1;while(nd)up(nd,k),nd>>=1;
}
bool vis[M];
inline void blk_upd(int nd,int k,int w){
	for(int i=0;i<M;i++)vis[i]=0;
	for(int i=max(tree[nd].l,ql);i<=min(tree[nd].r,qr);i++)if(b[i]==k&&a[i]>w){
		a[i]-=w;
		if(a[i]<pw[k]){
			int nw=calc(a[i]);
			if(!vis[nw])leaf_down(nd,nw),vis[nw]=1;
			b[i]=nw,leaf_up(nd,nw);
		}
	}
}
inline void updata(int nd,int l,int r,int k,int w){
	if(!tree[nd].cnt[k])return ;
	if(tree[nd].mx[k]<=w)return ;
	if(pl[l]>=ql&&pr[r]<=qr&&tree[nd].mn[k]-w>=pw[k])return upd(tree[nd],k,w);
	if(l==r)return blk_down(tree[nd],k),blk_upd(nd,k,w),blk_up(tree[nd],k);
	down(nd,k);
	if(idl<=mid)updata(ls,l,mid,k,w);
	if(idr>mid)updata(rs,mid+1,r,k,w);
	up(nd,k);
}
int qmn,qmx;ll qsum;
inline void blk_calc(node &u){
	for(int i=0;i<M;i++)qsum+=u.sum[i],chkmin(qmn,u.mn[i]),chkmax(qmx,u.mx[i]);
}
inline void blk_query(node &u){
	for(int i=max(u.l,ql);i<=min(u.r,qr);i++){
		qsum+=a[i],chkmin(qmn,a[i]),chkmax(qmx,a[i]);
	}
}
inline void query(int nd,int l,int r){
	if(pl[l]>=ql&&pr[r]<=qr)return blk_calc(tree[nd]);
	if(l==r)return blk_down(tree[nd]),blk_query(tree[nd]);
	down(nd);
	if(idl<=mid)query(ls,l,mid);
	if(idr>mid)query(rs,mid+1,r);
}
inline void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=calc(a[i]);
	num=(n-1)/B+1;
	for(int i=1;i<=num;i++){
		pl[i]=(i-1)*B+1,pr[i]=min(i*B,n);
		for(int j=pl[i];j<=pr[i];j++)bel[j]=i;
	}
	build(1,1,num);
	while(q--){
		int op=read();ql=read()^ans,qr=read()^ans,idl=bel[ql],idr=bel[qr];
		if(op==1){
			int w=read()^ans;
			for(int i=calc(w);i<M;i++)updata(1,1,num,i,w);
		}
		else{
			qmn=inf,qsum=qmx=0;query(1,1,num);
			write(qsum),putchar(' '),write(qmn),putchar(' '),write(qmx),puts("");
			// ans=qsum&mod;
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