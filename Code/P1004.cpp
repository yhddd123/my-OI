#include<bits/stdc++.h>
using namespace std;
const int maxn=310;

int n,a[maxn][maxn],dp[maxn<<1][maxn][maxn];
int u,v,w;
void sovle(){
	cin>>n;
	while(cin>>u>>v>>w){
		if(!u&&!v&&!w)break;
		a[u][v]=w;
	}
	memset(dp,-0x3f,sizeof(dp));
	dp[1][1][1]=a[1][1];
	for(int t=2;t<=n;t++){
		for(int i=1;i<=t;i++){
			for(int j=1;j<=t;j++){
				int ii=t+1-i,jj=t+1-j;
				dp[t][i][j]=max({dp[t-1][i][j],dp[t-1][i][j-1],dp[t-1][i-1][j],dp[t-1][i-1][j-1]});
				if(i!=j){
					dp[t][i][j]+=a[i][ii]+a[j][jj]; 
				}
				else dp[t][i][j]+=a[i][ii];
			}
		}
	}
	for(int t=n+1;t<=n*2-1;t++){
		for(int i=n;i>=t-n+1;i--){
			for(int j=n;j>=t-n+1;j--){
				int ii=t+1-i,jj=t+1-j;
//				cout<<t<<" "<<i<<" "<<ii<<" "<<j<<" "<<jj<<"\n";
				dp[t][i][j]=max({dp[t-1][i][j],dp[t-1][i][j-1],dp[t-1][i-1][j],dp[t-1][i-1][j-1]});
				if(i!=j){
					dp[t][i][j]+=a[i][ii]+a[j][jj]; 
				}
				else dp[t][i][j]+=a[i][ii];
			}
		}
	}
	cout<<dp[n*2-1][n][n];
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

