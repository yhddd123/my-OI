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

int n,k,a[maxn],ans;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int dp[maxn][25][2];
void dfs(int u,int fa){
	for(int i=0;i<=k;i++)dp[u][i][0]=a[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs(v,u);
			for(int j=1;j<=k;j++)dp[u][j][0]+=dp[v][j-1][0];
		}
	}
}
void dfs1(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dp[v][1][1]+=dp[u][0][0];
			for(int j=2;j<=k;j++){
				dp[v][j][1]+=dp[u][j-1][1]-dp[v][j-2][0];
			}
			dfs1(v,u);
		}
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();k=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(1,1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			dp[i][j][1]=dp[i][j][0];
//			cout<<dp[i][j][0]<<" ";
		}
//		cout<<"\n";
	}
	dfs1(1,1);
	for(int i=1;i<=n;i++)printf("%lld\n",dp[i][k][1]);
}
