// Problem: D - Many Palindromes on Tree
// Contest: AtCoder - AtCoder Regular Contest 198 (Div. 2)
// URL: https://atcoder.jp/contests/arc198/tasks/arc198_d
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-05-25 20:52:05
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
const int maxn=3010;
const int inf=1e9;
bool mbe;

int n,ans;
vector<int> e[maxn];
char s[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
bool vis[maxn][maxn];
int fa[maxn],dfn[maxn],idx,siz[maxn];
void dfs(int u){
	dfn[u]=++idx,siz[u]=1;
	for(int v:e[u]){
		if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
	}
}
bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
int find(int u,int v){
	int l=1,r=e[u].size()-1,res=0;
	while(l<=r){
		int mid=l+r>>1;
		if(dfn[e[u][mid]]<=dfn[v])res=mid,l=mid+1;
		else r=mid-1;
	}
	return e[u][res];
}
bool res[maxn][maxn];
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1);
	for(int u=1;u<=n;u++){
		for(int i=0;i<e[u].size();i++)if(e[u][i]==fa[u]){
			e[u][i]=e[u].back();e[u].pop_back();
			break;
		}
		sort(e[u].begin(),e[u].end(),[&](int u,int v){return dfn[u]<dfn[v];});
	}
	for(int i=1;i<=n;i++)vis[i][i]=1;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=i+1;j<=n;j++)if(s[j]=='1'){
			int u=i,v=j;
			while(!vis[u][v]){
				f[fd(u)]=fd(v),vis[u][v]=vis[v][u]=1;
				if(in(v,u))swap(u,v);
				if(in(u,v)){
					int p=find(u,v);
					if(p==v)break;
					u=p,v=fa[v];
				}
				else u=fa[u],v=fa[v];
			}
		}
	}
	// for(int i=1;i<=n;i++)cout<<fd(i)<<" ";cout<<"\n";
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)vis[i][j]=0;
	}
	for(int i=1;i<=n;i++)vis[i][i]=res[i][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int u=i,v=j;
			bool fl=1;
			vector<pii> pos;
			while(!vis[u][v]){
				pos.pb({u,v});vis[u][v]=vis[v][u]=1;
				if(fd(u)!=fd(v)){fl=0;break;}
				if(in(v,u))swap(u,v);
				if(in(u,v)){
					int p=find(u,v);
					if(p==v){u=v;break;}
					u=p,v=fa[v];
				}
				else u=fa[u],v=fa[v];
			}
			fl&=res[u][v];
			if(fl)++ans;
			for(auto[u,v]:pos)res[u][v]=res[v][u]=fl;
		}
	}
	printf("%lld\n",ans*2+n);
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