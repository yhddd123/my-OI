// Problem: B - Stolen Necklace
// Contest: AtCoder - AtCoder Regular Contest 215
// URL: https://atcoder.jp/contests/arc215/tasks/arc215_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-22 20:11:17
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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int pos[maxn],f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
pii edge[maxn];
int id[maxn];
vector<int> e[maxn];
void dfs(int u,int fa){
	a[u]=a[fa]^1;
	for(int v:e[u])if(v!=fa)dfs(v,u);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)pos[i]=0;
	for(int i=1;i<=2*n;i++)f[i]=i;
	for(int i=1;i<=2*n;i++){
		int x=read();
		if(pos[x])f[i]=fd(pos[x]),edge[x]={pos[x],i};
		else pos[x]=i;
	}
	int num=0;
	id[1]=++num;
	for(int i=1;i<2*n;i++){
		if(fd(i)!=fd(i+1)){
			id[i+1]=id[i];
			f[fd(i)]=fd(i+1);
		}
		else id[i+1]=++num;
	}
	for(int i=1;i<=num;i++)e[i].clear();
	for(int i=1;i<=n;i++){
		auto[u,v]=edge[i];
		e[id[u]].pb(id[v]),e[id[v]].pb(id[u]);
	}
	dfs(1,0);
	vector<int> ans;
	for(int i=1;i<2*n;i++)if(a[id[i]]!=a[id[i+1]])ans.pb(i);
	printf("%d\n",ans.size());
	for(int p:ans)printf("%d ",p);puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}