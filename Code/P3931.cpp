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

int n,rt;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
}
int dp[maxn];
bool vis[maxn];
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			if(vis[v])dp[u]+=e[i].w;
			else{
				dfs(v,u);
				dp[u]+=min(dp[v],e[i].w);
			}
		}
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();rt=read();
	for(int i=1;i<n;i++){
		int u,v,w;
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=n;i++)if(!e[head[i]].nxt&&i!=rt)vis[i]=1;
	dfs(rt,0);
	printf("%lld\n",dp[rt]);
}
