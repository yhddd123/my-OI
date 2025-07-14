#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=18;
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
int g[maxn][maxn];
int head[maxn],tot;
struct edgend{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int a[maxn],tp;
int dp[maxn][maxn],ans;
void dfs(int u,int fa){
	for(int j=1;j<=tp;j++)dp[u][a[j]]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		for(int j=1;j<=tp;j++){
			int sum=0;
			for(int k=1;k<=tp;k++)if(g[a[j]][a[k]])sum+=dp[v][a[k]];
			dp[u][a[j]]*=sum;
		}
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		g[u][v]=g[v][u]=1;
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int s=0;s<(1<<n);s++){
		tp=0;
		for(int i=0;i<n;i++)if(s&(1<<i))a[++tp]=i+1;
		dfs(1,0);
		for(int i=1;i<=tp;i++){
			if(n-tp&1)ans-=dp[1][a[i]];
			else ans+=dp[1][a[i]];
		}
	}
	printf("%lld\n",ans);
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
