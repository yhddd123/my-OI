// Problem: P5292 [HNOI2019] 校园旅行
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5292
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=5010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,p;
vector<int> e[maxn],g[maxn];
char a[maxn];
int vis[maxn],flag;
void dfs(int u,int fl){
	for(int v:e[u])if((a[u]==a[v]&&fl)||(a[u]!=a[v]&&!fl)){
		if(~vis[v]){
			if(vis[v]==vis[u])flag=1;
		}
		else{
			vis[v]=1-vis[u];dfs(v,fl);
			g[u].push_back(v),g[v].push_back(u);
		}
	}
}
queue<pii> q;
bool dp[maxn][maxn];
void work(){
	n=read();m=read();p=read();
	scanf("%s",a+1);
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
		if(a[u]==a[v])q.push({u,v}),dp[u][v]=dp[v][u]=1;
	}
	for(int k=0;k<2;k++){
		for(int i=1;i<=n;i++)vis[i]=-1;
		for(int i=1;i<=n;i++)if(vis[i]==-1){
			flag=0;vis[i]=0;dfs(i,k);
			if(flag)g[i].push_back(i);
		}
	}
	// for(int i=1;i<=n;i++){
		// for(int j:g[i])cout<<i<<" "<<j<<"\n";
	// }
	for(int i=1;i<=n;i++)q.push({i,i}),dp[i][i]=1;
	while(!q.empty()){
		int u1=q.front().first,u2=q.front().second;q.pop();
		for(int v1:g[u1]){
			for(int v2:g[u2])if(a[v1]==a[v2]&&!dp[v1][v2]){
				dp[v1][v2]=dp[v2][v1]=1;
				q.push({v1,v2});
			}
		}
	}
	while(p--){
		int u=read(),v=read();
		if(dp[u][v])printf("YES\n");
		else printf("NO\n");
	}
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
