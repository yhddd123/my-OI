#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans;
int g[maxn],w[maxn];
int dp[12][maxn][maxn];

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=0;i<(1<<n);i++){
		if((i<<1)&i)g[i]=0;
		else g[i]=1,w[i]=__builtin_popcount(i);
	}
	for(int i=0;i<(1<<n);i++)dp[1][i][w[i]]=g[i];
	for(int i=2;i<=n;i++){
		for(int s=0;s<(1<<n);s++){
			if(!g[s])continue;
			for(int j=w[s];j<=m;j++){
				for(int t=0;t<(1<<n);t++){
					if(!g[t]||((t<<1)&s)||((t>>1)&s)||(t&s))continue;
					dp[i][s][j]+=dp[i-1][t][j-w[s]];
				}
			}
			if(i==n)ans+=dp[i][s][m];
		}
	}
	printf("%lld\n",ans);
}
