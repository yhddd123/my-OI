// Problem: P10208 [JOI 2024 Final] 礼物交换 / Gift Exchange
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10208
// Memory Limit: 1024 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2025-10-15 10:04:59
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

int n,q;
int l[maxn],r[maxn];
struct node{
	int l,r,c;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};
set<node> s;
void split(int p){
	auto it=s.lower_bound({p,p,0});
	if((*it).r>p){
		auto[l,r,c]=*it;
		s.erase(it);
		s.insert({l,p,c}),s.insert({p+1,r,c});
	}
}
int ins(int l,int r,int c){
	split(l-1),split(r);
	// cout<<l<<" "<<r<<" "<<c<<endl;
	auto it=s.lower_bound({l,l,0});
	int mx=-n-1;
	while((*it).r<=r)mx=max(mx,(*it).c),it=s.erase(it);
	s.insert({l,r,c});
	return mx;
}
int pl[maxn],pr[maxn];
vector<int> pos[maxn];
vector<pii> ask[maxn];
int ans[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2];
void build(int nd,int l,int r){
	mn[nd]=inf;
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int p,int w){
    if(l==r){mn[nd]=w;return ;}
    if(p<=mid)modif(ls,l,mid,p,w);
    else modif(rs,mid+1,r,p,w);
    mn[nd]=min(mn[ls],mn[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mn[nd];
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)r[i]=read();
	for(int i=1;i<=n;i++)l[i]=read();
	s.insert({0,2*n+1,0});
	for(int i=1;i<=n;i++)pl[i]=ins(l[i],r[i],i);
	s.clear();
	s.insert({0,2*n+1,-n-1});
	for(int i=n;i;i--)pr[i]=-ins(l[i],r[i],-i);
	// for(int i=1;i<=n;i++)cout<<pl[i]<<" "<<pr[i]<<"\n";
	for(int i=1;i<=n;i++)pos[pr[i]].pb(i);
	q=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		ask[r].pb({l,i});
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		modif(1,1,n,i,pl[i]);
		for(int j:pos[i])modif(1,1,n,j,inf);
		for(auto[j,id]:ask[i])ans[id]=(query(1,1,n,j,i)>=j);
	}
	for(int i=1;i<=q;i++)puts(ans[i]?"Yes":"No");
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