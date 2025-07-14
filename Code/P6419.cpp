#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int head[maxn],tot;
struct edgend{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int a[maxn],fa[maxn],dep[maxn],tp[maxn];
bool vis[maxn];
int to[maxn][19];
int dis[maxn],d[maxn],s,t;
void dfs(int u){
	to[u][0]=fa[u];for(int i=1;i<=18;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u])continue;
		fa[v]=u;dep[v]=dep[u]+1;dis[v]=dis[u]+e[i].w;
		dfs(v);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=18;~i;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=18;~i;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
void dfs1(int u,int f){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f||!vis[v])continue;
		d[v]=d[u]+e[i].w;
		dfs1(v,u);
	}
}
void dfs2(int u,int lst){
	tp[u]=lst;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||vis[v])continue;
		dfs2(v,lst);
	}
}
int calc(int u,int v){
	return dis[u]+dis[v]-2*dis[lca(u,v)];
}
int ans[maxn],res;
void work(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	for(int i=1;i<=m;i++)a[i]=read();
	dfs(a[1]);
	if(m==1){
		for(int i=1;i<=n;i++)printf("%lld\n",calc(i,a[1]));
		return ;
	}
	for(int i=2;i<=m;i++){
		int u=a[i];
		while(!vis[u])vis[u]=1,res+=dis[u]-dis[fa[u]],u=fa[u];
	}
//	cout<<res<<"\n";
	res<<=1;
	s=a[1];for(int i=2;i<=m;i++)if(dis[a[i]]>dis[s])s=a[i];
	dfs1(s,s);
	t=a[1];for(int i=2;i<=m;i++)if(d[a[i]]>d[t])t=a[i];
//	cout<<s<<" "<<t<<"\n";
	for(int i=1;i<=n;i++)if(vis[i])dfs2(i,i);
	for(int i=1;i<=n;i++)if(vis[i]){
		ans[i]=res-max(calc(s,i),calc(t,i));
	}
	for(int i=1;i<=n;i++)if(!vis[i]){
		ans[i]=dis[i]-dis[tp[i]]+ans[tp[i]];
//		cout<<i<<" "<<tp[i]<<"\n";
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
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
