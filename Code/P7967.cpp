#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=55;
const int maxm=10010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],ans;
int fac[maxm],inv[maxm];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int dp[maxn][maxn][maxm];

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	fac[0]=inv[0]=fac[1]=inv[1]=1;
	for(int i=2;i<=m;i++)fac[i]=fac[i-1]*i%mod,inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=m;i++)inv[i]=inv[i-1]*inv[i]%mod;
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=1;k<=m;k++)dp[i][j][k]+=dp[i-1][j-1][k-1],dp[i][j][k]%=mod;
			for(int k=a[i];k<=m;k++)dp[i][j][k]+=dp[i-1][j][k-a[i]]*j*2%mod,dp[i][j][k]%=mod;
			for(int k=a[i]*2-1;k<=m;k++)dp[i][j][k]+=dp[i-1][j+1][k-a[i]*2+1]*j*(j+1)%mod,dp[i][j][k]%=mod;
		}
	}
	for(int i=n;i<=m;i++)ans+=C(m+n-i,n)*dp[n][1][i]%mod,ans%=mod;
	printf("%lld\n",ans);
}
