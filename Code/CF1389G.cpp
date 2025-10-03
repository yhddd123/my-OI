#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=300010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k,a[maxn];
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w=0){e[++tot]={head[u],v,w};head[u]=tot;}
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int scc[maxn],scct;
void tar(int u,int fl){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(i==(fl^1))continue;
		if(!dfn[v]){
			tar(v,i);
			lw[u]=min(lw[u],lw[v]);
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
	if(lw[u]==dfn[u]){
		scc[st[tp]]=++scct;
		while(st[tp--]!=u)scc[st[tp]]=scct;
	}
}
int c[maxn],w[maxn];
pii edge[maxn];
int val[maxn],d[maxn];
bool vis[maxn];
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int f[maxn],g[maxn];
void dfs(int u,int fa){
	f[u]=val[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||!d[v])continue;
		dfs(v,u);
		f[u]+=max(0ll,f[v]-e[i].w);
	}
	// cout<<u<<" "<<f[u]<<"\n";
}
void dfs1(int u,int fa){
	g[u]=f[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||!d[v])continue;
		int fu=f[u],fv=f[v];
		f[u]-=max(0ll,f[v]-e[i].w);
		f[v]+=max(0ll,f[u]-e[i].w);
		dfs1(v,u);
		f[u]=fu,f[v]=fv;
	}
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=k;i++)a[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=m;i++)w[i]=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
		edge[i]={u,v};
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i,0);
	for(int i=1;i<=n;i++)val[scc[i]]+=c[i];
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<=m;i++){
		auto[u,v]=edge[i];
		u=scc[u],v=scc[v];
		if(u==v)continue;
		add(u,v,w[i]),add(v,u,w[i]);
		d[u]++,d[v]++;
	}
	for(int i=1;i<=k;i++)vis[scc[a[i]]]=1;
	for(int i=1;i<=n;i++)ff[i]=i;
	queue<int> q;
	for(int i=1;i<=scct;i++)if(d[i]==1&&!vis[i])q.push(i);
	while(!q.empty()){
		int u=q.front();d[u]=0;q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(d[v]){
				d[v]--;val[v]+=val[u];
				ff[u]=v;
			}
			if(d[v]==1&&!vis[v])q.push(v);
		}
	}
	dfs(scc[a[1]],0);dfs1(scc[a[1]],0);
	// for(int i=1;i<=n;i++)cout<<scc[i]<<" ";cout<<"\n";
	// for(int i=1;i<=scct;i++)cout<<f[i]<<" "<<g[i]<<"\n";
	// for(int i=1;i<=scct;i++)cout<<fd(i)<<" ";cout<<"\n";
	// for(int i=1;i<=scct;i++)cout<<val[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)printf("%lld ",g[fd(scc[i])]);
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