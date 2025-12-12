// Problem: P11985 [JOIST 2025] 比太郎之旅 2 / Bitaro's Travel 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11985
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-12-03 22:40:53
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
const int maxn=300010;
const int inf=2.1e9;
bool mbe;

int n,m,q,l,a[maxn];
int f[maxn],nxt[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
vector<int> e[maxn];
int dfn[maxn],idx,siz[maxn];
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v)return ;
	if(a[u]<a[v])swap(u,v);
	e[u].pb(v);
	f[v]=u;
}
void dfs(int u){
	siz[u]=1;dfn[u]=++idx;
	for(int v:e[u]){
		dfs(v);siz[u]+=siz[v];
	}
}
bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
int get(pii u){return (u.fi-1)*m+u.se;}
int fx[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int to[19][maxn];
void work(){
	n=read();m=read();l=read();
	vector<pii> id;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[get({i,j})]=read(),id.pb({i,j});
	}
	sort(id.begin(),id.end(),[&](pii u,pii v){return a[get(u)]<a[get(v)];});
	for(int i=1;i<=n*m;i++)f[i]=i;
	id.pb({1,0});a[0]=inf;
	for(int i=0,j=0;i+1<id.size();i++){
		for(int k=0;k<4;k++){
			int nx=id[i].fi+fx[k][0],ny=id[i].se+fx[k][1];
			if(nx<=0||nx>n||ny<=0||ny>m||a[get({nx,ny})]>a[get(id[i])])continue;
			merge(get({nx,ny}),get(id[i]));
		}
		if(a[get(id[i])]<a[get(id[i+1])]){
			while(j<=i&&a[get(id[j])]+l<a[get(id[i+1])]){
				nxt[get(id[j])]=fd(get(id[j]));
				// cout<<get(id[j])<<" "<<fd(get(id[j]))<<"\n";
				j++;
			}
		}
	}
	for(int i=1;i<=n*m;i++)to[0][i]=nxt[i];
	for(int j=1;j<=18;j++){
		for(int i=1;i<=n*m;i++)to[j][i]=to[j-1][to[j-1][i]];
	}
	for(int i=n*m-1;~i;i--)if(!dfn[get(id[i])])dfs(get(id[i]));
	q=read();
	while(q--){
		int u=get({read(),read()}),v=get({read(),read()}),ans=0;
		for(int j=18;~j;j--)if(!in(to[j][u],v))u=to[j][u],ans+=1<<j;
		// cout<<u<<" "<<ans<<"\n";
		if(!in(nxt[u],v))ans=-1;
		else ++ans;
		printf("%d\n",ans);
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