#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,k;
int head[maxn],tot;
struct nd{
	int nxt,to,val;
}e[maxn<<1];
void add(int u,int v,int w){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].val=w;
	head[u]=tot;
}

int f[maxn][31],dep[maxn],len[maxn];

void dfs(int u,int fa){
	f[u][0]=fa;
	for(int i=1;1<<i<=dep[u];i++){
		f[u][i]=f[f[u][i-1]][i-1];
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dep[v]=dep[u]+1;
			len[v]=len[u]+e[i].val;
			dfs(v,u);
		}
	}
}

int lca(int u,int v){
	if(dep[u]>dep[v])swap(u,v);
	for(int i=log2(dep[v]);i>=0;i--){
		if(dep[f[v][i]]>=dep[u])v=f[v][i];
	}
	if(u==v)return u;
	for(int i=log2(dep[v]);i>=0;i--){
		if(f[u][i]!=f[v][i])u=f[u][i],v=f[v][i];
	}
	return f[u][0];
}

signed main(){
//	freopen("P2912_2.in","r",stdin);
	n=read();k=read();
	for(int i=1;i<n;i++){
		int u,v,w;
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
	}
	dfs(1,0);
	while(k--){
		int u,v;
		u=read();v=read();
		printf("%lld\n",len[u]+len[v]-len[lca(u,v)]*2);
	}
}

