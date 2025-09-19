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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn];
int dep[maxn],up[maxn],dis[maxn];
vector<int> e[maxn],g[maxn],h[maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int v:e[u])if(v!=fa)dfs(v,u);
}
void dfs1(int u){
	if(up[u])return ;
	up[u]=u;
	for(int v:g[u]){
		dfs1(v);
		if(dep[up[v]]<dep[up[u]])up[u]=up[v];
	}
}
bool vis[maxn];
void dfs2(int u){
	if(vis[u])return ;vis[u]=1;
	for(int v:h[u])dfs2(v);
}
void work(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=m;i++)a[i]=read();
	queue<int> q;
	for(int i=1;i<=m;i++)dis[a[i]]=1,q.push(a[i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u])if(!dis[v]){
			dis[v]=dis[u]+1,q.push(v);
		}
	}
	for(int u=1;u<=n;u++){
		for(int v:e[u])if(dis[v]==dis[u]+1)g[u].pb(v),h[v].pb(u);
	}
	for(int i=1;i<=m;i++)dfs1(a[i]);
	sort(a+1,a+m+1,[&](int u,int v){return dep[u]>dep[v];});
	vector<int> ans;
	for(int i=1;i<=m;i++)if(!vis[a[i]]){
		ans.pb(up[a[i]]);
		dfs2(up[a[i]]);
	}
	printf("%d\n",ans.size());
	for(int u:ans)printf("%d ",u);puts("");
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