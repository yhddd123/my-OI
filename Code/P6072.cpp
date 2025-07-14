// Problem: P6072 『MdOI R1』Path
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6072
// Memory Limit: 244 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-05-30 12:05:21
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
const int maxn=200010;
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
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int tree[maxn<<7][2],idx,sum[maxn<<7],rt[maxn];
void insert(int &o,int x){
	if(!o)o=++idx;int nd=o;
	for(int i=31;~i;i--){
		int v=(x>>i)&1;
		if(!tree[nd][v])tree[nd][v]=++idx;
		nd=tree[nd][v];sum[nd]++;
	}
}
int calc(int nd,int x){
	int res=0;
	for(int i=31;~i;i--){
		int v=(x>>i)&1;
		
		if(sum[tree[nd][v^1]])res|=(1<<i),nd=tree[nd][v^1];
		else nd=tree[nd][v];
	}
	return res;
}
int siz[maxn],dis[maxn],son[maxn],fa[maxn];
void dfs(int u){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dis[v]=dis[u]^e[i].w;dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int f[maxn],g[maxn];
int dfn[maxn],tim,rnk[maxn];
void dfs1(int u){
	rnk[dfn[u]=++tim]=u;
	if(!son[u]){
		insert(rt[u],dis[u]);
		return ;
	}
	dfs1(son[u]);rt[u]=rt[son[u]],f[u]=f[son[u]];
	insert(rt[u],dis[u]);f[u]=max(f[u],calc(rt[u],dis[u]));
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs1(v);
	}
	for(int i=dfn[son[u]]+siz[son[u]];i<dfn[u]+siz[u];i++){
		insert(rt[u],dis[rnk[i]]);
		f[u]=max(f[u],calc(rt[u],dis[rnk[i]]));
	}
}
vector<int> id;bool vis[maxn];
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	dfs(1);dfs1(1);
	// for(int i=1;i<=n;i++)cout<<dis[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	int ans=0,x=1,y=1;
	for(int i=1;i<=n;i++){
		insert(rt[0],dis[i]);
		int v=calc(rt[0],dis[i]);
		// cout<<i<<" "<<v<<"\n";
		if(ans<v)ans=v,x=i;
	}
	for(int i=1;i<=n;i++)if(dis[i]==(ans^dis[x]))y=i;
	// cout<<ans<<" "<<x<<" "<<y<<"\n";
	while(x!=1){
		id.push_back(x);vis[x]=1;
		x=fa[x];
	}
	reverse(id.begin(),id.end());
	for(int u:id){
		g[u]=g[fa[u]];
		insert(rt[n+1],dis[fa[u]]);g[u]=max(g[u],calc(rt[n+1],dis[fa[u]]));
		for(int i=head[fa[u]];i;i=e[i].nxt){
			int v=e[i].to;if(v==u||v==fa[fa[u]])continue;
			for(int j=dfn[v];j<dfn[v]+siz[v];j++){
				insert(rt[n+1],dis[rnk[j]]);
				g[u]=max(g[u],calc(rt[n+1],dis[rnk[j]]));
			}
		}
		// cout<<u<<" "<<g[u]<<"\n";
	}
	id.clear();
	while(y!=1){
		id.push_back(y);vis[y]=1;
		y=fa[y];
	}
	reverse(id.begin(),id.end());
	for(int u:id){
		g[u]=g[fa[u]];
		insert(rt[n+2],dis[fa[u]]);g[u]=max(g[u],calc(rt[n+2],dis[fa[u]]));
		for(int i=head[fa[u]];i;i=e[i].nxt){
			int v=e[i].to;if(v==u||v==fa[fa[u]])continue;
			for(int j=dfn[v];j<dfn[v]+siz[v];j++){
				insert(rt[n+2],dis[rnk[j]]);
				g[u]=max(g[u],calc(rt[n+2],dis[rnk[j]]));
			}
		}
		// cout<<u<<" "<<g[u]<<"\n";
	}
	for(int i=2;i<=n;i++)if(!vis[i])g[i]=ans;
	// for(int i=2;i<=n;i++)cout<<g[i]<<" ";cout<<"\n";
	ans=0;for(int i=2;i<=n;i++)ans=max(ans,f[i]+g[i]);
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
