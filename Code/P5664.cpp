#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int maxn=110;
const int maxm=2010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,m,a[maxn][maxm],ans=1;
int sum[maxn],dp[maxn][maxn<<1];

signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();sum[i]+=a[i][j];
			if(sum[i]>mod)sum[i]-=mod; 
		}
		ans*=(sum[i]+1);ans%=mod;
	}
	ans=(ans-1+mod)%mod;
	for(int c=1;c<=m;c++){
		memset(dp,0,sizeof(dp));
		dp[0][n]=1;
		for(int i=1;i<=n;i++){
			for(int j=n-i;j<=n+i;j++){
				dp[i][j]=(dp[i-1][j]+dp[i-1][j-1]*a[i][c]%mod+dp[i-1][j+1]*(sum[i]-a[i][c])%mod)%mod;
			}
		}
		for(int i=1;i<=n;i++){
			ans-=dp[n][n+i];
			if(ans<0)ans+=mod;
		}
	}
	printf("%lld\n",ans%mod);
}

