#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=250010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
}
int f[maxn][21],g[maxn][21],dep[maxn];
int dfn[maxn],cnt;
void dfs(int u,int fa,int w){
	dep[u]=dep[fa]+1;
	dfn[u]=++cnt;
	f[u][0]=fa;
	g[u][0]=w;
	for(int i=1;(1<<i)<=dep[u];i++){
		f[u][i]=f[f[u][i-1]][i-1];
		g[u][i]=min(g[u][i-1],g[f[u][i-1]][i-1]);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa)dfs(v,u,e[i].w);
	}
}
int x,d[maxn];
bool vis[maxn];
bool cmp(int u,int v){return dfn[u]<dfn[v];}
int st[maxn],tp;
int lca(int u,int v){
	if(u==v)return u;
	if(dep[u]<dep[v])swap(u,v);
	for(int i=20;i>=0;i--){
		if(dep[f[u][i]]>=dep[v])u=f[u][i];
	}
	if(u==v)return u;
	for(int i=20;i>=0;i--){
		if(f[u][i]!=f[v][i])u=f[u][i],v=f[v][i];
	}
	return f[u][0];
}
int getval(int u,int v){
	int res=inf;
	for(int i=20;i>=0;i--){
		if(dep[f[u][i]]>=dep[v]){
			res=min(res,g[u][i]);
			u=f[u][i];
		}
	}
	return res;
}
void build(){
	sort(d+1,d+x+1,cmp);
	tp=0;st[++tp]=1;
	tot=0;head[1]=0;
	for(int i=1;i<=x;i++){
		int l=lca(st[tp],d[i]);
		if(l!=st[tp]){
			while(dfn[l]<dfn[st[tp-1]]){
				add(st[tp-1],st[tp],getval(st[tp],st[tp-1]));
				tp--;
			}
			if(st[tp-1]!=l){
				head[l]=0;
				add(l,st[tp],getval(st[tp],l));
				st[tp]=l;
			}
			else{
				add(l,st[tp],getval(st[tp],l));
				tp--;
			}
		}
		head[d[i]]=0;
		st[++tp]=d[i];
	}
	for(int i=1;i<tp;i++)add(st[i],st[i+1],getval(st[i+1],st[i]));
}
int dp[maxn];
void dfs1(int u){
	dp[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs1(v);
		if(vis[v])dp[u]+=e[i].w;
		else dp[u]+=min(dp[v],e[i].w);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<n;i++){
		int u,v,w;
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
	}
	dfs(1,0,0);
	m=read();
	while(m--){
		x=read();
		for(int i=1;i<=x;i++){
			d[i]=read();
			vis[d[i]]=true;
		}
		build();
		dfs1(1);
		printf("%lld\n",dp[1]);
		for(int i=1;i<=x;i++)vis[d[i]]=false;
	}
}
