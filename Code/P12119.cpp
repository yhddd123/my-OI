// Problem: P12119 [NordicOI 2025] 垃圾收集 / Garbage Collection
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12119
// Memory Limit: 1 MB
// Time Limit: 5500 ms
// Written by yhm.
// Start codeing:2025-04-11 12:36:50
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

int n,w,h,ans;
tuple<int,int,int> a[maxn];
int lsh[maxn],len;
int lsh1[maxn],len1;
vector<tuple<int,int,int>> que[maxn];
int mx[maxn<<2],tag[maxn<<2];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
void upd(int nd,int w){mx[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
}
void work(){
	n=read();w=read(),h=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read(),v=read();
		a[i]={x,y,v};
		lsh[++len]=x,lsh[++len]=x+w;
		lsh1[++len1]=y,lsh1[++len1]=y+h-1;
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	sort(lsh1+1,lsh1+len1+1),len1=unique(lsh1+1,lsh1+len1+1)-lsh1-1;
	for(int i=1;i<=n;i++){
		auto[x,y,v]=a[i];
		int l=lower_bound(lsh1+1,lsh1+len1+1,y)-lsh1;
		int r=lower_bound(lsh1+1,lsh1+len1+1,y+h-1)-lsh1;
		que[lower_bound(lsh+1,lsh+len+1,x)-lsh].pb({l,r,v});
		que[lower_bound(lsh+1,lsh+len+1,x+w)-lsh].pb({l,r,-v});
	}
	for(int i=1;i<=len;i++){
		for(auto[l,r,v]:que[i])updata(1,1,len1,l,r,v);
		ans=max(ans,mx[1]);
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