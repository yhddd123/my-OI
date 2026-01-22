// Problem: P10656 [ROI 2017] 学习轨迹 (Day 2)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10656
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-22 14:42:36
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m;
int ca[maxn],va[maxn],cb[maxn],vb[maxn];
int id[maxn<<1],to[maxn];
int sa[maxn],sb[maxn];
int pl[maxn],pr[maxn];
struct node{
	int val;
	pii p1,p2;
}ans;
bool operator<(node u,node v){return u.val<v.val;}
node get(int l1,int r1,int l2,int r2){
	if(l1>r1)l1=r1=0;
	if(l2>r2)l2=r2=0;
	return {sa[r1]-(l1?sa[l1-1]:0)+sb[r2]-(l2?sb[l2-1]:0),{l1,r1},{l2,r2}};
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
pii mx[maxn<<2];int tag[maxn<<2];
void upd(int nd,int w){mx[nd].fi+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
}
void modif(int nd,int l,int r,int p,int w){
	if(l==r){mx[nd]={w,l};return ;}
	if(tag[nd])down(nd);
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	mx[nd]=max(mx[ls],mx[rs]);
}
void build(int nd,int l,int r){
	mx[nd]={-inf,l};tag[nd]=0;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
int st1[maxn],tp1,st2[maxn],tp2;
node calc(bool fl=0){
	node ans={0,{0,0},{0,0}};
	for(int i=1;i<=n+m;i++)id[i]=0;
	for(int i=1;i<=n;i++)id[ca[i]]=i;
	for(int i=1;i<=m;i++)to[i]=id[cb[i]];
	int p=0;for(int i=1;i<=n;i++)if(sa[i]>=sa[n]/2){p=i;break;}
	for(int i=1;i<=m;i++)pl[i]=1,pr[i]=n;
	for(int i=1;i<=m;i++)if(to[i]){
		if(to[i]<=p)pl[i]=to[i]+1;
		else pr[i]=to[i]-1;
	}
	build(1,1,m);
	tp1=tp2=0;
	for(int i=1;i<=m;i++){
		while(tp1&&pl[st1[tp1]]<=pl[i]){
			updata(1,1,m,st1[tp1-1]+1,st1[tp1],sa[pl[st1[tp1]]-1]);
			tp1--;
		}
		modif(1,1,m,i,-sb[i-1]);
		st1[++tp1]=i,updata(1,1,m,st1[tp1-1]+1,st1[tp1],-sa[pl[st1[tp1]]-1]);
		while(tp2&&pr[st2[tp2]]>=pr[i]){
			updata(1,1,m,st2[tp2-1]+1,st2[tp2],-sa[pr[st2[tp2]]]);
			tp2--;
		}
		st2[++tp2]=i,updata(1,1,m,st2[tp2-1]+1,st2[tp2],sa[pr[st2[tp2]]]);
		int j=mx[1].se;
		int p1=lower_bound(st1+1,st1+tp1+1,j)-st1,p2=lower_bound(st2+1,st2+tp2+1,j)-st2;
		// cout<<j<<" "<<i<<" "<<pl[st1[p1]]<<" "<<pr[st2[p2]]<<" "<<get(pl[st1[p1]],pr[st2[p2]],j,i).val+sb[i]<<"\n";
		ans=max(ans,get(pl[st1[p1]],pr[st2[p2]],j,i));
	}
	if(fl)swap(ans.p1,ans.p2);
	return ans;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)ca[i]=read();
	for(int i=1;i<=n;i++)va[i]=read();
	for(int i=1;i<=m;i++)cb[i]=read();
	for(int i=1;i<=m;i++)vb[i]=read();
	for(int i=1;i<=n;i++)sa[i]=sa[i-1]+va[i];
	for(int i=1;i<=m;i++)sb[i]=sb[i-1]+vb[i];
	ans=max(get(0,0,1,m),get(1,n,0,0));
	ans=max(ans,calc());
	swap(ca,cb),swap(va,vb),swap(sa,sb),swap(n,m);
	ans=max(ans,calc(1));
	printf("%lld\n%lld %lld\n%lld %lld\n",ans.val,ans.p1.fi,ans.p1.se,ans.p2.fi,ans.p2.se);
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