// Problem: P6326 Shopping
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6326
// Memory Limit: 125 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=510;
const int maxm=4010;
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
struct nd{
	int nxt,to;
}e[maxm<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int sum,siz[maxn],mx[maxn],rt;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1;mx[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		getrt(v,u);siz[u]+=siz[v];mx[u]=max(mx[u],siz[v]);
	}
	mx[u]=max(mx[u],sum-siz[u]);
	if(mx[u]<mx[rt])rt=u;
}
int dfn[maxn],rnk[maxn],ed[maxn],idx;
void dfs1(int u,int fa){
	rnk[dfn[u]=++idx]=u;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		dfs1(v,u);siz[u]+=siz[v];
	}
	ed[dfn[u]]=idx;
}
int dp[maxn][maxm],ans;
int w[maxn],c[maxn],d[maxn],num[maxn];
void sovle(int u){
	vis[u]=1;idx=0;dfs1(u,u);
	for(int i=1;i<=idx+1;i++){
		for(int j=0;j<=m;j++)dp[i][j]=0;
	}
	for(int i=idx;i;i--){
		int W=w[rnk[i]],C=c[rnk[i]],D=min(m/C,d[rnk[i]])-1,len=0;
		if(D<0)continue;
		for(int j=1;j<=D;j<<=1)D-=j,num[++len]=j;
		if(D)num[++len]=D;
		for(int j=C;j<=m;j++)dp[i][j]=max(dp[i][j],dp[i+1][j-C]+W);
		for(int j=1;j<=len;j++){
			for(int k=m;k>=C*num[j];k--)dp[i][k]=max(dp[i][k],dp[i][k-C*num[j]]+W*num[j]);
		}
		for(int j=0;j<=m;j++)dp[i][j]=max(dp[i][j],dp[ed[i]+1][j]);
	}
	ans=max(ans,dp[1][m]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		rt=0;sum=siz[v];getrt(v,v);sovle(rt);
	}
}
void work(){
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<=n;i++)vis[i]=false;
	n=read();m=read();ans=0;
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++)d[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	mx[rt=0]=inf;sum=n;getrt(1,1);sovle(rt);
	printf("%d\n",ans);
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
	
	T=read();
	while(T--)work();
}
