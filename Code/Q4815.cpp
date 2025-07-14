#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=40010;
const int maxm=3010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],w[maxn],rt,sum;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1,w[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		getrt(v,u);siz[u]+=siz[v];
		w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)rt=u;
}
int ans[maxn],f[maxn][maxm],g[maxn][maxm];
int dfn1[maxn],idx1,rnk1[maxn];
int dfn2[maxn],idx2,rnk2[maxn];
int dep[maxn],dis[maxn];
void dfs(int u,int fa){
	siz[u]=1;dep[u]=dep[fa]+1,dis[u]=dis[fa]+a[u];
	rnk1[dfn1[u]=++idx1]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v]||v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];
	}
	rnk2[dfn2[u]=++idx2]=u;
}
void sovle(int u){
	vis[u]=1;idx1=idx2=0;dfs(u,0);int s=siz[u];
	if(s<k)return ;
	// cout<<u<<"\n";
	for(int i=1;i<=s+1;i++){
		for(int j=1;j<=k;j++)f[i][j]=g[i][j]=0;
	}
	for(int i=s;i;i--){
		int u=rnk1[i];
		for(int j=1;j<=k;j++)f[i][j]=max(f[i+1][j-1]+a[u],f[i+siz[u]][j]);
	}
	for(int i=1;i<=s;i++){
		int u=rnk2[i];
		for(int j=1;j<=k;j++)g[i][j]=max(g[i-1][j-1]+a[u],g[i-siz[u]][j]);
	}
	// for(int i=1;i<=s;i++){
		// cout<<i<<" "<<rnk1[i]<<" "<<rnk2[i]<<" a\n";
		// for(int j=1;j<=k;j++)cout<<f[i][j]<<" ";cout<<"\n";
		// for(int j=1;j<=k;j++)cout<<g[i][j]<<" ";cout<<"\n";
	// }
	for(int i=1;i<=s;i++){
		int u=rnk1[i];
		for(int j=0;j<=k-dep[u];j++)ans[u]=max(ans[u],f[i+1][j]+g[dfn2[u]-siz[u]][k-dep[u]-j]+dis[u]);
		// cout<<u<<" "<<rnk1[i+1]<<" "<<rnk2[dfn2[u]-siz[u]]<<" "<<ans[u]<<"\n";
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		sum=siz[v];getrt(v,u);sovle(rt);
	}
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	sum=n;getrt(1,0);sovle(rt);
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
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
	
	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
