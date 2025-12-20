// Problem: P10430 [JOIST 2024] 鱼 3 / Fish 3
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10430
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-12-19 14:24:24
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,d,q,a[maxn];
vector<pii> que[maxn];
int ans[maxn];
#define lb(x) (x&(-x))
struct bit{
	int tree[maxn];
	void upd(int x,int w){
		while(x<=n)tree[x]+=w,x+=lb(x);
	}
	int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	void upd(int l,int r,int w){
		// cout<<l<<" "<<r<<" "<<w<<"\n";
		upd(l,w),upd(r+1,-w);}
}tk,tb;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){mn[nd]=a[l];return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mn[nd]=min(mn[ls],mn[rs]);
}
void upd(int nd,int w){mn[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]);
}
int query(int nd,int l,int r,int p){
	if(l==r)return mn[nd];
	if(tag[nd])down(nd);
	if(p<=mid)return query(ls,l,mid,p);
	else return query(rs,mid+1,r,p);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mn[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void work(){
	n=read();d=read();
	for(int i=1;i<=n;i++)a[i]=read();
	q=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		que[r].pb({l,i});
	}
	build(1,1,n);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++){
		int p=i;
		while(p>1){
			int lst=fd(p-1);
			int vp=query(1,1,n,p),vq=query(1,1,n,p-1);
			// cout<<p<<" "<<vp<<" "<<vq<<"\n";
			if(vp<vq){
				int t=(vq-vp+d-1)/d;
				tk.upd(lst,p-1,-t),tb.upd(lst,p-1,p*t);
				tb.upd(1,lst-1,(p-lst)*t);
				updata(1,1,n,lst,p-1,-t*d);
				f[fd(p)]=lst;
				p=lst;
			}
			else{
				if(vp-d<vq){
					f[fd(p)]=lst;
					p=lst;
				}
				else break;
			}
		}
		for(auto[l,id]:que[i]){
			if(query(1,1,n,l,i)<0)ans[id]=-1;
			else ans[id]=tk.que(l)*l+tb.que(l);
		}
		// for(int j=1;j<=i;j++)cout<<tk.que(j)*j+tb.que(j)<<" ";cout<<"\n";
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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