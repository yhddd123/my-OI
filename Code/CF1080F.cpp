// Problem: CF1080F Katya and Segments Sets
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1080F
// Memory Limit: 500 MB
// Time Limit: 3500 ms
// Written by yhm.
// Start codeing:2025-04-02 22:23:52
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
const int maxn=100010;
const int maxk=600010;
const int inf=1e9;
bool mbe;

int n,q,k;
vector<pii> a[maxn];
vector<pii> upd[maxk];
int lsh[maxk],len;
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int mn[maxn<<7],lc[maxn<<7],rc[maxn<<7];
int rt[maxk],idx;
void updata(int &nd,int l,int r,int p,int w){
	int lst=nd;nd=++idx;mn[nd]=mn[lst],ls=lc[lst],rs=rc[lst];
	if(l==r){mn[nd]=max(mn[nd],w);return ;}
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	mn[nd]=min(mn[ls],mn[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
	if(!nd)return 0;
	if(l>=ql&&r<=qr)return mn[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();q=read();k=read();
	for(int i=1;i<=k;i++){
		int l=read(),r=read(),id=read();
		a[id].pb({l,r});
		lsh[++len]=l,lsh[++len]=r;
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++){
		for(auto [l,r]:a[i]){
			l=lower_bound(lsh+1,lsh+len+1,l)-lsh;
			r=lower_bound(lsh+1,lsh+len+1,r)-lsh;
			upd[r].pb({l,i});
		}
	}
	for(int i=1;i<=len;i++){
		rt[i]=rt[i-1];
		for(auto[l,id]:upd[i])updata(rt[i],1,n,id,l);
	}
	while(q--){
		int l=read(),r=read(),x=read(),y=read();
		x=lower_bound(lsh+1,lsh+len+1,x)-lsh;
		y=upper_bound(lsh+1,lsh+len+1,y)-lsh-1;
		puts(query(rt[y],1,n,l,r)>=x?"yes":"no");fflush(stdout);
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