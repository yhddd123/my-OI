#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=2000010;
const int inf=1e9;
const db eps=1e-9;
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
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
vector<int> g[maxn];
int dfn[maxn],idx,lw[maxn];
bool vis[maxn];
int st[maxn],tp;
int scc[maxn],siz[maxn],scct,num[maxn];
void tar(int u,int fa){
	dfn[u]=lw[u]=++idx;
	vis[u]=1;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		if(!dfn[v]){
			tar(v,u);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(vis[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		scct++;
		siz[scct]=1;
		scc[st[tp]]=scct;
		vis[st[tp]]=0;
		while(st[tp--]!=u){
			siz[scct]++;
			scc[st[tp]]=scct;
			vis[st[tp]]=0;
		}
	}
}
int pw[maxn];
int dp[maxn],sum[maxn],ans;
void dfs(int u,int fa){
	dp[u]=pw[siz[u]+num[u]];
	sum[u]=num[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);sum[u]+=sum[v]+1;
		dp[u]*=(dp[v]+pw[sum[v]+1])%mod,dp[u]%=mod;
	}
	dp[u]+=mod-pw[sum[u]],dp[u]%=mod;
	ans+=dp[u]*pw[m-sum[u]-(fa!=0)]%mod,ans%=mod;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
		g[u].push_back(v);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i,0);
	memset(head,0,sizeof(head));tot=0;
	for(int u=1;u<=n;u++){
		for(int v:g[u]){
			if(scc[u]==scc[v])num[scc[u]]++;
			else add(scc[u],scc[v]),add(scc[v],scc[u]);
		}
	}
	pw[0]=1;for(int i=1;i<maxn;i++)pw[i]=pw[i-1]*2%mod;
	dfs(1,0);
	printf("%lld\n",ans);
}
