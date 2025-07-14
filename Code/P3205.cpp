#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 19650827
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn];
int dp[maxn][maxn][2];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)dp[i][i][0]=1;
	for(int len=2;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			if(a[i]<a[i+1])dp[i][j][0]+=dp[i+1][j][0];
			if(a[i]<a[j])dp[i][j][0]+=dp[i+1][j][1];
			if(a[j]>a[i])dp[i][j][1]+=dp[i][j-1][0];
			if(a[j]>a[j-1])dp[i][j][1]+=dp[i][j-1][1];
			dp[i][j][0]%=mod,dp[i][j][1]%=mod;
		}
	}
	printf("%lld\n",(dp[1][n][0]+dp[1][n][1])%mod);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
