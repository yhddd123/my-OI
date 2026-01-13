// Problem: P14945 不想玩原神
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14945
// Memory Limit: 512 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2026-01-13 15:29:00
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=2010;
const int maxm=500010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn][maxn];
bitset<maxn> ans[maxm];
vector<tuple<int,int,int>> ask[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
bitset<maxn> tree[maxn<<2];
void build(int nd,int l,int r){
	tree[nd].reset();
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int id){
	for(int j=l;j<=r;j++)tree[nd].set(a[id][j]);
	if(l==r)return ;
	modif(ls,l,mid,id);
	modif(rs,mid+1,r,id);
}
bitset<maxn> query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)|query(rs,mid+1,r,ql,qr);
}
void sovle(int l,int r,vector<tuple<int,int,int,int,int>> &upd){
	if(!upd.size())return ;
	if(r-l+1<=20){
		for(auto[l1,r1,l2,r2,id]:upd){
			for(int i=l1;i<=r1;i++){
				for(int j=l2;j<=r2;j++)ans[id].set(a[i][j]);
			}
		}
		return ;
	}
	for(int i=l;i<=r;i++)ask[i].clear();
	vector<tuple<int,int,int,int,int>> ul,ur;
	for(auto[l1,r1,l2,r2,id]:upd){
		if(r1<=mid)ul.pb({l1,r1,l2,r2,id});
		else if(l1>mid)ur.pb({l1,r1,l2,r2,id});
		else{
			ask[l1].pb({l2,r2,id}),ask[r1].pb({l2,r2,id});
		}
	}
	build(1,1,n);
	for(int i=mid;i>=l;i--){
		modif(1,1,n,i);
		for(auto[l,r,id]:ask[i])ans[id]|=query(1,1,n,l,r);
	}
	build(1,1,n);
	for(int i=mid+1;i<=r;i++){
		modif(1,1,n,i);
		for(auto[l,r,id]:ask[i])ans[id]|=query(1,1,n,l,r);
	}
	sovle(l,mid,ul),sovle(mid+1,r,ur);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
	}
	vector<tuple<int,int,int,int,int>> upd;
	q=read();
	for(int i=1;i<=q;i++){
		int l1=read(),r1=read(),l2=read(),r2=read();
		upd.pb({l1,r1,l2,r2,i});
	}
	sovle(1,n,upd);
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i].count());
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