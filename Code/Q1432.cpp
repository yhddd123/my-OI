#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define ls nd<<1
#define rs nd<<1|1
using namespace std;
const int maxm=200010;
const int maxn=2010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
int dp[maxn][maxn][2];
int ans[maxn][maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=2000;
	for(int i=1;i<=n;i++){
		int tp;
		if(i==1)tp=n;
		else tp=(n-i)/(i-1);
		dp[0][0][0]=dp[0][0][1]=1;
		for(int j=0;j<=n;j++){
			for(int k=0;k<=tp;k++){
				if(!j&&!k)continue;
				if(k){
					dp[j][k][0]=dp[j][k-1][1],dp[j][k][0]%=mod;
					if(k-i-1>=0)dp[j][k][0]+=mod-dp[j][k-i-1][1],dp[j][k][0]%=mod;
				}
				else dp[j][k][0]=0;
				if(j){
					dp[j][k][1]=dp[j-1][k][0],dp[j][k][1]%=mod;
					if(j-i-1>=0)dp[j][k][1]+=mod-dp[j-i-1][k][0],dp[j][k][1]%=mod;
				}
				else dp[j][k][1]=0;
				if(j>=k&&(j+k)/(k+1)==i)ans[j][k]=(dp[j][k][0]+dp[j][k][1])%mod;
				if(k)dp[j][k][1]+=dp[j][k-1][1],dp[j][k][1]%=mod;
				if(j)dp[j][k][0]+=dp[j-1][k][0],dp[j][k][0]%=mod;
			}
		}
	}
	T=read();
	while(T--){
		int u=read(),v=read();
		if(u<v)swap(u,v);
		printf("%lld\n",ans[u][v]);
	}
}
