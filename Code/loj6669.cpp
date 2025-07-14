// Problem: #6669. Nauuo and Binary Tree
// Contest: LibreOJ
// URL: https://loj.ac/p/6669
// Memory Limit: 256 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2024-08-16 14:53:31
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=3010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
vector<int> e[maxn];
int dis[maxn][maxn];
int que(int u,int v){
	printf("? %lld %lld\n",u,v);fflush(stdout);
	int x=read();return x;
	// return dis[u][v];
}
int dep[maxn],fa[maxn],siz[maxn],son[maxn];
void dfs(int u){
	siz[u]=1;
	for(int v:e[u])if(v){
		dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	if(e[u].size()==2&&son[u]!=e[u][0])swap(e[u][0],e[u][1]);
}
int dfn[maxn],idx,rnk[maxn],ed[maxn];
void dfs1(int u){
	rnk[dfn[u]=++idx]=u;ed[u]=u;
	if(!son[u])return ;
	dfs1(son[u]);
	for(int v:e[u])if(v&&v!=son[u])dfs1(v);
	ed[u]=ed[son[u]];
}
vector<int> id[maxn];

vector<int> g[maxn];
priority_queue<pii> q;
bool vis[maxn];
void dij(int s){
	for(int i=1;i<=n;i++)dis[s][i]=inf,vis[i]=0;
	dis[s][s]=0;q.push({0,s});
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int v:g[u]){
			if(dis[s][v]>dis[s][u]+1){
				dis[s][v]=dis[s][u]+1;
				q.push({-dis[s][v],v});
			}
		}
	}
}

void work(){
	n=read();
	
	// for(int i=2;i<=n;i++){
		// int p=read();
		// g[i].push_back(p),g[p].push_back(i);
	// }
	// for(int i=1;i<=n;i++)dij(i);
	
	for(int i=2;i<=n;i++)dep[i]=que(1,i);
	for(int i=2;i<=n;i++)id[dep[i]].push_back(i);
	for(int i=1;i<=n;i++)e[i].resize(2);
	for(int i=1;i<=n;i++){
		if(!id[i].size())break;
		dfs(1),idx=0,dfs1(1);
		for(int u:id[i]){
			int x=1;
			while(e[x][0]){
				int d=(dep[ed[x]]+dep[u]-que(ed[x],u))/2;
				if(d>dep[ed[x]]){x=ed[x];break ;}
				x=rnk[dfn[x]+d-dep[x]];
				if(!e[x][1])break;
				x=e[x][1];
			}
			if(!e[x][0])e[x][0]=u,fa[u]=x;
			else e[x][1]=u,fa[u]=x;
		}
	}
	printf("! ");for(int i=2;i<=n;i++)printf("%lld ",fa[i]);printf("\n");fflush(stdout);
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
