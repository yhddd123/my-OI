// Problem: P12082 [Ynoi1998] Frühlingsbeginn
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12082
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-24 16:02:18
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,ans;
pii a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
multiset<int> s;
int mx[maxn<<2],pos[maxn<<2];
void up(int nd){
	mx[nd]=max(mx[ls],mx[rs]);
	if(mx[ls]<pos[rs])pos[nd]=pos[rs];
	else pos[nd]=pos[ls];
}
void build(int nd,int l,int r){
	if(l==r){
		s[l].insert(l);
		mx[nd]=*--s[l].end();
		pos[nd]=mx[nd]==l?l+1:l;
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd);
}
void modif(int nd,int l,int r,int p,int w){
	if(l==r){
		if(w>0)s[l].insert(w);
		else s[l].erase(s[l].find(-w));
		mx[nd]=*--s[l].end();
		pos[nd]=mx[nd]==l?l+1:l;
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	up(nd);
}
int query(int nd,int l,int r,int p,int &w){
	if(p<=l){
		if(w>=pos[nd]){w=max(w,mx[nd]);return r+1;}
		if(l==r)return l;
	}
	if(p<=mid){
		int res=query(ls,l,mid,p,w);
		if(res<=mid)return res;
		return query(rs,mid+1,r,p,w);
	}
	else return query(rs,mid+1,r,p,w);
}
void work(){
	n=read();q=read();
	build(1,1,n);
	for(int t=1;t<=q;t++){
		int o=read();
		if(o==1){
			int u=read(),v=max(read(),u);a[u]=v;
			modif(1,1,n,u);
		}
		else{
			int p=read()^ans,w=a[p];
			ans=query(1,1,n,p,w);
			write(ans),puts("");
		}
	}
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}