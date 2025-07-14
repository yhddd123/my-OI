// Problem: P10998 【MX-J3-T3+】Tuple+
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10998
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-09-02 19:01:29
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=300010;
const int inf=1e6;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans;
int a[maxn][3],d[maxn];
vector<pii> g[maxn];
vector<int> e[maxn];
int vis[maxn],bk[maxn];
map<int,bool> mp;
int get(int u,int v,int w){
	return min({u,v,w})*inf*inf+max({min(u,v),min(u,w),min(v,w)})*inf+max({u,v,w});
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		a[i][0]=u,a[i][1]=v,a[i][2]=w;
		d[u]++,d[v]++,d[w]++;
		mp[get(u,v,w)]=1;
	}
	for(int i=1;i<=m;i++){
		sort(a[i],a[i]+3,[&](int u,int v){return d[u]<d[v];});
		g[a[i][0]].push_back({a[i][1],a[i][2]});
	}
	mems(d,0);
	for(int i=1;i<=n;i++){
		vector<int> id;
		for(pii p:g[i]){
			int u=p.fi,v=p.se;
			d[u]++,d[v]++;
			id.pb(u),id.pb(v);
		}
		// cout<<i<<" "<<g[i].size()<<" "<<id.size()<<"\n";
		for(pii p:g[i]){
			int u=p.fi,v=p.se;
			if(d[u]<d[v])swap(u,v);
			else if(d[u]==d[v]&&u>v)swap(u,v);
			e[u].push_back(v);
		}
		for(int u:id)if(bk[u]!=i){
			bk[u]=i;
			for(int v:e[u])vis[v]=u;
			for(int v:e[u]){
				for(int vv:e[v])if(vis[vv]==u&&mp.find(get(u,v,vv))!=mp.end())++ans;
			}
		}
		for(int u:id)vis[u]=d[u]=0,e[u].clear();
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
