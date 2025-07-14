#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;int ans=inf;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int d[maxn],f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int dp[maxn],sum[maxn],dep[maxn];
void dfs(int u,int fa){
	int v1=0,v2=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		if(!v1)v1=v;
		else if(!v2)v2=v;
	}
	dp[u]=(dp[v1]+dp[v2])+sum[v1]+sum[v2]+min(sum[v1],sum[v2])+1;
	sum[u]=(sum[v1]+sum[v2])*2+1;
	dep[u]=max(dep[v1],dep[v2])+1;
	// cout<<u<<" "<<dp[u]<<" "<<sum[u]<<" "<<v1<<" "<<v2<<"\n";
}
void dfs1(int u,int fa){
	if(d[u]<=2&&dep[u]<=32)ans=min(ans,(int)dp[u]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		if(d[u]==1&&dep[v]<=32)ans=min(ans,(int)dp[v]);
		int valu1=dp[u],valu2=sum[u],valu3=dep[u],valv1=dp[v],valv2=sum[v],valv3=dep[v];
		int v1=fa,v2=0;
		for(int j=head[u];j;j=e[j].nxt){
			int vv=e[j].to;if(vv==fa||v==vv)continue;
			if(!v1)v1=vv;
			else v2=vv;
		}
		dp[u]=(dp[v1]+dp[v2])+sum[v1]+sum[v2]+min(sum[v1],sum[v2])+1;
		sum[u]=(sum[v1]+sum[v2])*2+1;
		dep[u]=max(dep[v1],dep[v2])+1;
		// cout<<u<<" "<<v<<" "<<v1<<" "<<v2<<" "<<dp[u]<<" "<<sum[u]<<"\n";
		if(d[v]==1&&dep[u]<=32){
			// cout<<u<<" "<<v<<" "<<dp[u]<<"\n";
			ans=min(ans,(int)dp[u]);
		}
		v1=u;v2=0;
		for(int j=head[v];j;j=e[j].nxt){
			int vv=e[j].to;if(vv==u)continue;
			v2=vv;
		}
		dp[v]=(dp[v1]+dp[v2])+sum[v1]+sum[v2]+min(sum[v1],sum[v2])+1;
		sum[v]=(sum[v1]+sum[v2])*2+1;
		dep[v]=max(dep[v1],dep[v2])+1;
		if(d[v]==2&&dep[v]<=32){
			ans=min(ans,dp[v]);
		}
		// cout<<u<<" "<<v<<" "<<v1<<" "<<v2<<" "<<dp[v]<<"\n";
		dfs1(v,u);
		dp[u]=valu1,sum[u]=valu2,dep[u]=valu3,dp[v]=valv1,sum[v]=valv2,dep[v]=valv3;
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
		d[u]++,d[v]++;
		if(fd(u)==fd(v)){puts("NIE");return ;}
		f[fd(u)]=fd(v);
	}
	for(int i=1;i<=n;i++)if(d[i]>3){puts("NIE");return ;}
	int rt=0;for(int i=1;i<=n;i++)if(d[i]<=1)rt=i;
	dfs(rt,0);
	dfs1(rt,0);
	if(n==1)ans=min(ans,0ll);
	if(ans==inf)puts("NIE");
	else printf("%lld\n",ans);
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