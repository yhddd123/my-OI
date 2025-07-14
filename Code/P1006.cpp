// Problem: P1006 [NOIP2008 提高组] 传纸条
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1006
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=55;

int n,m,a[maxn][maxn],dp[maxn<<1][maxn][maxn];
int u,v,w;
void sovle(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
	memset(dp,-0x3f,sizeof(dp));
	dp[2][1][1]=a[1][1];
	for(int t=3;t<=n+m;t++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int ii=t-i,jj=t-j;
				if(ii<1||ii>m||jj<1||jj>m)continue;
				dp[t][i][j]=max({dp[t-1][i][j],dp[t-1][i][j-1],dp[t-1][i-1][j],dp[t-1][i-1][j-1]});
				if(i!=j)dp[t][i][j]+=a[i][ii]+a[j][jj];
				else dp[t][i][j]+=a[i][ii];
				// cout<<t<<" "<<i<<" "<<j<<" "<<ii<<" "<<jj<<"\n";
			}
		}
	}
	cout<<dp[n+m][n][n];
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	T=1;
	while(T--)sovle();
}