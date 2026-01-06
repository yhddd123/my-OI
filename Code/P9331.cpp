// Problem: P9331 [JOIST 2023] 护照 / Passport
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9331
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-06 17:01:38
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
const int inf=1e18;
bool mbe;

int n,q;
vector<pii> e[maxn<<2];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int lc[maxn<<2],rc[maxn<<2],rt,idx;
void build(int &nd,int l,int r){
	if(l==r){
		nd=l;
		return ;
	}
	nd=++idx;
	build(ls,l,mid),build(rs,mid+1,r);
	e[ls].pb({nd,0}),e[rs].pb({nd,0});
}
void updata(int nd,int l,int r,int ql,int qr,int id,int w){
	if(l>=ql&&r<=qr){
		e[nd].pb({id,w});
		return ;
	}
	if(ql<=mid)updata(ls,l,mid,ql,qr,id,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,id,w);
}
int d1[maxn<<2],d2[maxn<<2],dis[maxn<<2];
bool vis[maxn<<2];
void sovle(int *dis){
	priority_queue<pii> q;
	queue<int> q1;
	for(int i=1;i<=idx;i++)q.push({-dis[i],i});
	for(int i=1;i<=idx;i++)vis[i]=0;
	while(!q.empty()){
		while(!q1.empty()){
			int u=q1.front();q1.pop();
			if(vis[u])continue;vis[u]=1;
			for(auto[v,w]:e[u]){
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					if(!w)q1.push(v);
					else q.push({-dis[v],v});
				}
			}
		}
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(auto[v,w]:e[u]){
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!w)q1.push(v);
				else q.push({-dis[v],v});
			}
		}
	}
}
void work(){
	n=read();idx=2*n;
	build(rt,1,n);
	for(int i=1;i<=n;i++){
		int l=read(),r=read();
		e[i+n].pb({i,1});
		updata(rt,1,n,l,r,i+n,0);
	}
	for(int i=1;i<=idx;i++)d1[i]=inf;d1[1]=0;
	sovle(d1);
	for(int i=1;i<=idx;i++)d2[i]=inf;d2[n]=0;
	sovle(d2);
	for(int i=1;i<=idx;i++)dis[i]=d1[i]+d2[i];
	sovle(dis);
	q=read();
	while(q--){
		int u=read();
		printf("%lld\n",dis[u]>=inf?-1:dis[u]);
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