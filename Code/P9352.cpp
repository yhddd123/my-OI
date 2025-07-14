#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int to[maxn][21],dep[maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	to[u][0]=fa;
	for(int i=1;i<=20;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa)dfs(v,u);
	}
}
int lca(int u,int v){
	if(u==v)return u;
	if(dep[u]<dep[v])swap(u,v);
	for(int i=20;i>=0;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=20;i>=0;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
int dp[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(a[u],a[v]);add(a[v],a[u]);
	}
	for(int i=1;i<=n;i++)f[i]=i;
	dfs(1,0);
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			v=fd(v);
			if(v<u){
				f[v]=u;
				dp[u]=max(dp[u],dp[v]+dis(u,v));
			}
		}
	}
	printf("%lld\n",dp[n]);
}
