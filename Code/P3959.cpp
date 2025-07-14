#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
using namespace std;
const int maxn=12;
const int maxm=4100;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,num,ans=inf;
int e[maxn][maxn],g[maxn];
int to[maxm];
int dp[maxm][maxn];
void work(){
	n=read();m=read();num=(1<<n)-1;
	memset(e,0x3f,sizeof(e));
	for(int i=0;i<n;i++)e[i][i]=0;
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1,w=read();
		e[u][v]=e[v][u]=min(e[u][v],w);
		g[u]|=(1<<v);g[v]|=(1<<u);
	}
	for(int i=0;i<n;i++)g[i]|=(1<<i);
	for(int i=1;i<=num;i++){
		for(int j=0;j<n;j++)if(i&(1<<j))to[i]|=g[j];
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<n;i++)dp[1<<i][0]=0;
	for(int i=1;i<=num;i++){
		for(int s=i-1;s;s=(s-1)&i)if((to[s]&i)==i){
			int t=i^s,res=0;
			for(int j=0;j<n;j++)if(t&(1<<j)){
				int mn=inf;
				for(int k=0;k<n;k++)if(s&(1<<k))mn=min(mn,e[j][k]);
				res+=mn;
			}
			for(int j=1;j<=n;j++)dp[i][j]=min(dp[i][j],dp[s][j-1]+res*j);
		}
//		for(int j=1;j<=n;j++)cout<<dp[i][j]<<" ";
//		cout<<"\n";
	}
	for(int i=0;i<=n;i++)ans=min(ans,dp[num][i]);
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
