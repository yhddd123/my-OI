// Problem: P9047 [PA2021] Poborcy podatkowi
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9047
// Memory Limit: 512 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2024-08-08 14:53:23
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dp[maxn][4],f[2][1010][2][4];
void dfs(int u,int fa){
	int d=0,dd=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);++d;
	}
	d=min(d+1,500ll);
	f[0][d][0][0]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dd++;dd=min(dd,d-1);
		for(int j=d-dd;j<=d+dd;j++){
			for(int fl=0;fl<2;fl++){
				for(int s=0;s<4;s++)f[1][j][fl][s]=f[0][j][fl][s];
			}
		}
		for(int j=d-dd;j<=d+dd;j++){
			for(int fl=0;fl<2;fl++){
				if(f[1][j][fl][0]>-inf){
					for(int s=0;s<4;s++){	
						f[0][j][fl][s]=max(f[0][j][fl][s],f[1][j][fl][0]+dp[v][(s-1+4)%4]+e[i].w);
					}
				}
				for(int s=0;s<4;s++)if(f[1][j][fl][s]>-inf){
					f[0][j][fl][s]=max(f[0][j][fl][s],f[1][j][fl][s]+dp[v][0]);
					f[0][j+1][fl][s]=max(f[0][j+1][fl][s],f[1][j][fl][s]+dp[v][0]+e[i].w);
					f[0][j][fl^1][s]=max(f[0][j][fl^1][s],f[1][j][fl][s]+dp[v][1]+e[i].w);
					f[0][j-1][fl][s]=max(f[0][j-1][fl][s],f[1][j][fl][s]+dp[v][2]+e[i].w);
					f[0][j][fl][s]=max(f[0][j][fl][s],f[1][j][fl][s]+dp[v][3]+e[i].w);
				}
			}
		}
	}
	for(int i=0;i<4;i++)dp[u][i]=f[0][d][0][i];
	// cout<<u<<" "<<dp[u][0]<<" "<<dp[u][1]<<" "<<dp[u][2]<<" "<<dp[u][3]<<"\n";
	for(int j=1;j<=2*d;j++){
		for(int fl=0;fl<2;fl++){
			for(int s=0;s<4;s++)f[0][j][fl][s]=f[1][j][fl][s]=-inf;
		}
	}
}
vector<pii> g[maxn];
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		g[u].push_back({v,w}),g[v].push_back({u,w});
	}
	srand(time(0));
	for(int i=1;i<=n;i++)random_shuffle(g[i].begin(),g[i].end());
	for(int i=1;i<=n;i++){
		for(int j=0;j<g[i].size();j++)add(i,g[i][j].fi,g[i][j].se);
	}
	mems(f,-0x3f);dfs(1,0);
	printf("%lld\n",dp[1][0]);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("monkey.in","r",stdin);
	// freopen("monkey.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}