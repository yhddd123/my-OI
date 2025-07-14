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

int n,m,q;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int to[maxn][21],g[maxn][21];
int dep[maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=1;i<=20;i++)to[u][i]=to[to[u][i-1]][i-1],g[u][i]=max(g[u][i-1],g[to[u][i-1]][i-1]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			to[v][0]=u;g[v][0]=e[i].w;
			dfs(v,u);
		}
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	int ans=0;
	for(int i=20;i>=0;i--)if(dep[to[u][i]]>=dep[v])ans=max(ans,g[u][i]),u=to[u][i];
	if(u==v)return ans;
	for(int i=20;i>=0;i--)if(to[u][i]!=to[v][i])ans=max(ans,max(g[u][i],g[v][i])),u=to[u][i],v=to[v][i];
	ans=max(ans,max(g[u][0],g[v][0]));
	return ans;
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		for(int j=2*(m-i+1);j<=n;j+=(m-i+1)){
			if(fd(m-i+1)==fd(j))continue;
			f[fd(m-i+1)]=fd(j);
			add(m-i+1,j,i);
			add(j,m-i+1,i);
		}
	}
	dfs(1,1);
	while(q--){
		int u,v;
		u=read();v=read();
		printf("%lld\n",lca(u,v));
	}
}
