#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=2010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,s,t;
int dp[maxn][maxn];

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();s=read();t=read();
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(i==s||i==t){
				dp[i][j]+=dp[i-1][j-1],dp[i][j]%=mod;
				dp[i][j]+=dp[i-1][j],dp[i][j]%=mod;
			}
			else{
				dp[i][j]+=dp[i-1][j+1]*j%mod,dp[i][j]%=mod;
				int num=j-2+(i<s)+(i<t);
				dp[i][j]+=dp[i-1][j-1]*num%mod,dp[i][j]%=mod;
			}
		}
	}
	printf("%lld\n",dp[n][1]);
}
