#include<bits/stdc++.h>
#define int long long
#define mod 9999973
using namespace std;
const int maxn=110;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans;
int dp[maxn][maxn][maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<=m-j;k++){
				dp[i][j][k]=dp[i-1][j][k];
				//不放
				if(j>=1)dp[i][j][k]+=dp[i-1][j-1][k]*(m-j+1-k)%mod;
				dp[i][j][k]%=mod;
				if(k>=1)dp[i][j][k]+=dp[i-1][j+1][k-1]*(j+1)%mod;
				dp[i][j][k]%=mod;
				//放一个
				if(j>=2)dp[i][j][k]+=(m-j+2-k)*(m-j+1-k)/2%mod*dp[i-1][j-2][k]%mod;
				dp[i][j][k]%=mod;
				if(k>=1)dp[i][j][k]+=dp[i-1][j][k-1]*(m-j-k+1)%mod*j%mod;
				dp[i][j][k]%=mod;
				if(k>=2)dp[i][j][k]+=(j+2)*(j+1)/2%mod*dp[i-1][j+2][k-2]%mod;
				dp[i][j][k]%=mod;
				//放两个
				if(i==n){
					ans+=dp[i][j][k],ans%=mod;
//					cout<<dp[i][j][k]<<" ";
				}
			}
//			printf("\n");
		}
	}
	printf("%lld\n",ans);
}
