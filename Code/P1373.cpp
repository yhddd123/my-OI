#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int maxn=810;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,p,a[maxn][maxn],ans;
int dp[maxn][maxn][20][2];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();p=read();p++;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();a[i][j]%=p;
			dp[i][j][a[i][j]][0]=1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<p;k++){
				for(int l=0;l<=1;l++){
					dp[i][j][k][l]=(dp[i][j][k][l]+dp[i-1][j][(k+a[i][j]*(2*l-1)+p)%p][l^1]+dp[i][j-1][(k+a[i][j]*(2*l-1)+p)%p][l^1])%mod;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ans=(ans+dp[i][j][0][1])%mod;
		}
	}
	printf("%d\n",ans);
}
