// Problem: P4747 [CERC2017] Intrinsic Interval
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4747
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-11-20 16:48:32
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
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
pii mn[maxn<<2];int tag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){mn[nd]={l,-l};return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mn[nd]=min(mn[ls],mn[rs]);
}
void upd(int nd,int w){mn[nd].fi+=w;tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mn[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
int st1[maxn],tp1,st2[maxn],tp2;
vector<pii> que[maxn];
set<pii> s;
pii ans[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	q=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		que[r].pb({l,i});
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		while(tp1&&a[i]<a[st1[tp1]]){
			updata(1,1,n,st1[tp1-1]+1,st1[tp1],a[st1[tp1]]-a[i]);
			tp1--;
		}
		while(tp2&&a[i]>a[st2[tp2]]){
			updata(1,1,n,st2[tp2-1]+1,st2[tp2],-a[st2[tp2]]+a[i]);
			tp2--;
		}
		st1[++tp1]=i,st2[++tp2]=i;
		for(auto[l,id]:que[i])s.insert({l,id});
		while(s.size()){
			auto[l,id]=*--s.end();
			pii p=query(1,1,n,1,l);
			if(p.fi==i){
				ans[id]={-p.se,i};
				s.erase(--s.end());
			}
			else break;
		}
	}
	for(int i=1;i<=q;i++)printf("%d %d\n",ans[i].fi,ans[i].se);
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