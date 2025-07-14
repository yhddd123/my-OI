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

int n,m;
vector<int> g[maxn],e[maxn];
bool vis1[maxn],vis2[maxn],vis[maxn];
int dp[maxn],d[maxn];
void dfs1(int u){
	vis1[u]=1;
	for(int v:g[u]){
		if(!vis1[v])dfs1(v);
	}
}
void dfs2(int u){
	vis2[u]=1;
	for(int v:e[u]){
		if(!vis2[v])dfs2(v);
	}
}
void dfs(int u,int fa){
	if(vis[u])return ;
	vis[u]=1;
	for(int v:g[u]){
		if(vis1[v]&&vis2[v])++d[v],dfs(v,u);
	}
}
queue<int> q;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		g[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1);dfs2(2);
	if(!vis1[2]){
		printf("0\n");
		return 0;
	}
	dfs(1,0);
	q.push(1);dp[1]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:g[u]){
			if(vis1[v]&&vis2[v]){
				d[v]--;
				dp[v]=(dp[v]+dp[u])%inf;
				if(!d[v])q.push(v);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(d[i]){
			printf("inf\n");
			return 0;
		}
	}
	printf("%lld\n",dp[2]);
}
